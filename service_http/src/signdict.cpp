 
 
/**
 * @file signdict.cpp
 * @brief SignDict implementation.
 *  
 **/

#include "signdict.h"

#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

/** 
 * @brief SignDict structure
 */
struct SignDict {
    u_int size_;            /** size of SignDict */
    u_int index_size_;      /** size of level-1 index */
    u_int prefix_width_;    /** bytes of prefix */
    u_int suffix_width_;    /** bytes of suffix */
    u_int value_width_;     /** bytes of value */

    u_int *index_;          /** index buffer */
    u_char *suffix_buf_;    /** suffix buffer */
    u_char *value_buf_;     /** value buffer */

    u_int iprefix_;         /** cursor of index buffer during insertion */
    u_int isuffix_;         /** cursor of suffix buffer during insertion */
};

/** 
 * @brief Calculate optimal prefix width given size of SignDict
 * 
 * @param size size of SignDict.
 * 
 * @return optimal prefix width
 */
static u_int __calculate_prefix_width(u_int size);

/** 
 * @brief Do binary search in suffix buffer.
 * 
 * @param suffix target suffix.
 * @param suffix_buf beginning of suffix buffer.
 * @param begin_pos beginning position of binary search range.
 * @param end_pos end position of binary search range.
 * @param suffix_width bytes of suffix
 * @param pos position of target suffix
 * 
 * @return  0 if found
 *         =1 if not found
 */
static int __bsearch(const u_char *suffix, const u_char *suffix_buf, u_int begin_pos, u_int end_pos, u_int suffix_width, u_int *pos);

/** 
 * @brief Get prefix_width bytes of given sign.
 * 
 * @param sign_buf pointer to signs
 * @param prefix_width bytes of prefix. should be less than 4.
 * 
 * @return prefix represented by int
 */
u_int __get_prefix(u_int *sign_buf, u_int prefix_width);

/** 
 * @brief Get suffix_width bytes.
 *        ATTENTION: The sign_buf is rearranged. Make sure to make a copy
 *                   if the original sign is intended to be keeped.
 * 
 * @param sign_buf pointer to sign.
 * @param prefix_width bytes of prefix.
 * 
 * @return pointer to beginning of suffix 
 */
u_char* __get_suffix(u_int *sign_buf, u_int prefix_width);

#define DICT_BIN_MAGIC_NUMBER 0x0000FEFF
#define DICT_BIN_HEADER_LEN 8
#define SIGN_WIDTH (64 / 8)
#define MAX_VALUE_WIDTH 1024

SignDict_t* signdict_new(u_int size, u_int prefix_width, u_int value_width)
{
    SignDict_t *dict;

    if(size <= 0 || prefix_width < 0 || prefix_width >= 4 
                 || value_width <= 0 || value_width > MAX_VALUE_WIDTH) {
        return NULL;
    }

    if((dict = (SignDict_t*)malloc(sizeof(SignDict_t))) == NULL) {
        return NULL;
    }

    dict->size_ = size;
    if(prefix_width == 0) {
        dict->prefix_width_ = __calculate_prefix_width(size);
    } else {
        dict->prefix_width_ = prefix_width;
    }
    dict->value_width_ = value_width;

    dict->index_size_ = (1 << (8 * dict->prefix_width_)) + 1;
    dict->suffix_width_ = SIGN_WIDTH - dict->prefix_width_;

    if((dict->index_ = (u_int*)malloc(sizeof(u_int) * dict->index_size_)) == NULL) {
        signdict_delete(dict);
        return NULL;
    }
    if((dict->suffix_buf_ = (u_char*)malloc(sizeof(char) * dict->suffix_width_ * dict->size_)) == NULL) {
        signdict_delete(dict);
        return NULL;
    }
    if((dict->value_buf_ = (u_char*)malloc(sizeof(char) * dict->value_width_ * dict->size_)) == NULL) {
        signdict_delete(dict);
        return NULL;
    }

    dict->iprefix_ = 0;
    dict->isuffix_ = 0;

    return dict;
}

int signdict_delete(SignDict_t *dict)
{
    if(dict == NULL) {
        return SIGNDICT_OK;
    }

    if(dict->index_ != NULL) {
        free(dict->index_);
    }
    if(dict->suffix_buf_ != NULL) {
        free(dict->suffix_buf_);
    }
    if(dict->value_buf_ != NULL) {
        free(dict->value_buf_);
    }
    free(dict);

    return SIGNDICT_OK;
}

u_int signdict_value_width(const SignDict_t *dict)
{
    if(dict != NULL) {
        return dict->value_width_;
    } else {
        return 0;
    }
}

u_int signdict_size(const SignDict_t *dict)
{
    if(dict != NULL) {
        return dict->size_;
    } else {
        return 0;
    }
}

int signdict_insert_one(SignDict_t *dict, const u_int sign[2], const u_char *value_buf)
{
    u_int sign_copy[2];
    u_int previous_prefix = 0;
    u_int current_prefix = 0;
    u_char *current_suffix = NULL;
    u_int i;

    if(dict == NULL || sign == NULL || value_buf == NULL) {
        return SIGNDICT_FAIL;
    }

    sign_copy[0] = sign[0];
    sign_copy[1] = sign[1];
    previous_prefix = dict->iprefix_;
    current_prefix = __get_prefix(sign_copy, dict->prefix_width_);
    current_suffix = __get_suffix(sign_copy, dict->prefix_width_);

    if(dict->isuffix_ >= dict->size_) {
        return SIGNDICT_ERR_DICT_FULL;
    }
    if(dict->isuffix_ != 0) {
        // key disordered
        if(current_prefix < previous_prefix) {
            return SIGNDICT_ERR_DISORDERED_KEY;
        }
        // key duplicated
        if(current_prefix == previous_prefix) {
            if(memcmp(dict->suffix_buf_ + (dict->isuffix_ - 1) * dict->suffix_width_, current_suffix, dict->suffix_width_) == 0) {
                return SIGNDICT_ERR_DUPLICATE_KEY;
            }
        }
        if(current_prefix != previous_prefix) {
            for(i = previous_prefix + 1; i <= current_prefix; i++) {
                dict->index_[i] = dict->isuffix_;
            }
            dict->iprefix_ = current_prefix;
        }
    } else {
        // the first insertion
        for(i = 0; i <= current_prefix; i++) {
            dict->index_[i] = dict->isuffix_;
        }
        dict->iprefix_ = current_prefix;
    }
    memcpy(dict->suffix_buf_ + dict->isuffix_ * dict->suffix_width_, current_suffix, dict->suffix_width_);
    memcpy(dict->value_buf_ + dict->isuffix_ * dict->value_width_, value_buf, dict->value_width_);
    dict->isuffix_++;
    
    return SIGNDICT_OK;
}

int signdict_insert_batch(SignDict_t *dict, const u_int *signs, const u_char *values, u_int count)
{
    u_int c = 0;
    u_int sign_copy[2];
    int result;

    if(dict == NULL || signs == NULL || values == NULL || count <= 0 || count > dict->size_) {
        return SIGNDICT_FAIL;
    }

    while(c < count) {
        sign_copy[0] = signs[c * 2];
        sign_copy[1] = signs[c * 2 + 1];
        if((result = signdict_insert_one(dict, sign_copy, values + c * dict->value_width_)) != SIGNDICT_OK ) {
            return result;
        }
        c++;
    }

    return SIGNDICT_OK;
}

int signdict_finalize_insertion(SignDict_t *dict) {
    u_int i;

    if(dict == NULL) {
        return SIGNDICT_FAIL;
    }

    for(i = dict->iprefix_ + 1; i < dict->index_size_; i++) {
        dict->index_[i] = dict->isuffix_;
    }
    if(dict->isuffix_ < dict->size_) {
        memset(dict->suffix_buf_ + dict->isuffix_ * dict->suffix_width_, 
               0, 
               dict->suffix_width_ * (dict->size_ - dict->isuffix_));
        memset(dict->value_buf_ + dict->isuffix_ * dict->value_width_, 
               0, 
               dict->value_width_ * (dict->size_ - dict->isuffix_));
    }

    return SIGNDICT_OK;
}

int signdict_search(const SignDict_t *dict, const u_int sign[2], u_char *value)
{
    u_int sign_copy[2];
    u_int prefix;
    u_char *suffix;
    u_int begin_pos;
    u_int end_pos;
    u_int pos;
    int found;

    if(dict == NULL || sign == NULL || value == NULL) {
        return SIGNDICT_FAIL;
    }

    sign_copy[0] = sign[0];
    sign_copy[1] = sign[1];
    prefix = __get_prefix(sign_copy, dict->prefix_width_);
    suffix = __get_suffix(sign_copy, dict->prefix_width_);
    begin_pos = dict->index_[prefix];
    end_pos = dict->index_[prefix + 1];

    if(begin_pos == end_pos) {
        return SIGNDICT_ERR_NOT_FOUND;
    }
    found = __bsearch(suffix, dict->suffix_buf_, begin_pos, end_pos - 1, dict->suffix_width_, &pos);
    if(found == -1) {
        return SIGNDICT_ERR_NOT_FOUND;
    } else {
        memcpy(value, dict->value_buf_ + pos * dict->value_width_, dict->value_width_);
        return SIGNDICT_OK;
    }
}

int signdict_dump(const SignDict_t *dict, FILE *fp)
{
    if(dict == NULL || fp == NULL) {
        return SIGNDICT_FAIL;
    }

    u_int header[DICT_BIN_HEADER_LEN] = {DICT_BIN_MAGIC_NUMBER, dict->size_, dict->prefix_width_, dict->value_width_};
    if(fwrite(header, sizeof(header), 1, fp) < 1) {
        return SIGNDICT_FAIL;
    }
    if(fwrite(dict->index_, sizeof(u_int), dict->index_size_, fp) < dict->index_size_) {
        return SIGNDICT_FAIL;
    }
    if(fwrite(dict->suffix_buf_, dict->suffix_width_, dict->size_, fp) < dict->size_) {
        return SIGNDICT_FAIL;
    }
    if(fwrite(dict->value_buf_, dict->value_width_, dict->size_, fp) < dict->size_) {
        return SIGNDICT_FAIL;
    }

    return SIGNDICT_OK;
}

SignDict_t* signdict_load(FILE *fp)
{
    SignDict_t *dict;
    u_int header[DICT_BIN_HEADER_LEN] = {0};
    u_int size;
    u_int prefix_width;
    u_int value_width;

    if(fread(header, sizeof(header), 1, fp) < 1) {
        return NULL;
    }
    if(header[0] != DICT_BIN_MAGIC_NUMBER) {
        return NULL;
    }
    size = header[1];
    prefix_width = header[2];
    value_width = header[3];
    
    if((dict = signdict_new(size, prefix_width, value_width)) == NULL) {
        return NULL;
    }
    if(fread(dict->index_, sizeof(u_int), dict->index_size_, fp) < dict->index_size_) {
        signdict_delete(dict);
        return NULL;
    }
    if(fread(dict->suffix_buf_, dict->suffix_width_, dict->size_, fp) < dict->size_) {
        signdict_delete(dict);
        return NULL;
    }
    if(fread(dict->value_buf_, dict->value_width_, dict->size_, fp) < dict->size_) {
        signdict_delete(dict);
        return NULL;
    }

    return dict;
}

int signdict_is_equal(const SignDict_t *lhs, const SignDict_t *rhs)
{
    if(lhs == rhs) {
        return 0;
    }
    if(lhs == NULL || rhs == NULL) {
        return -1;
    }

    if(lhs->size_ != rhs->size_) {
        return -1;
    }
    if(lhs->index_size_ != rhs->index_size_) {
        return -1;
    }
    if(lhs->prefix_width_ != rhs->prefix_width_) {
		return -1;
	}
    if(lhs->suffix_width_ != rhs->suffix_width_) {
		return -1;
	}
    if(lhs->value_width_ != rhs->value_width_) {
		return -1;
	}

    if(0 != memcmp(lhs->index_, rhs->index_, sizeof(u_int) * lhs->index_size_)) {
		return -1;
	}
    if(0 != memcmp(lhs->suffix_buf_, rhs->suffix_buf_, lhs->suffix_width_ * lhs->size_)) {
		return -1;
	}
    if(0 != memcmp(lhs->value_buf_, rhs->value_buf_, lhs->value_width_ * lhs->size_)) {
		return -1;
	}

    return 0;
}

static u_int __calculate_prefix_width(u_int size)
{
    if(size < 261000u) {
        return 1u;
    } else if(size < 67000000u) {
        return 2u;
    } else {
        return 3u;
    }
}

static int __bsearch(const u_char *suffix, const u_char *suffix_buf, u_int begin_pos, u_int end_pos, u_int suffix_width, u_int *pos)
{
    u_int low = begin_pos;
    u_int high = end_pos;
    u_int middle;

    while(low < high) {
        middle = low + (high - low) / 2;
        if(memcmp(suffix_buf + middle * suffix_width, suffix, suffix_width) < 0) {
            low = middle + 1;
        } else {
            high = middle;
        }
    } 
    if(memcmp(suffix_buf + low * suffix_width, suffix, suffix_width) == 0) {
        *pos = low;
        return 0;
    } else {
        return -1;
    }
}

u_int __get_prefix(u_int *sign_buf, u_int prefix_width)
{
    return sign_buf[0] >> ((sizeof(u_int) - prefix_width) * 8);
}

u_char* __get_suffix(u_int *sign_buf, u_int prefix_width)
{
    sign_buf[0] = htonl(sign_buf[0]);
    sign_buf[1] = htonl(sign_buf[1]);
    return (u_char*)sign_buf + prefix_width;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
