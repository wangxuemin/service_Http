/**
 * @file signdict.h
 * @brief SignDict interface.
 *  
 **/

#ifndef  __SIGNDICT_H_
#define  __SIGNDICT_H_

#include <ul_def.h>
#include <stdio.h>

struct SignDict;
typedef struct SignDict SignDict_t;

const int SIGNDICT_OK = 0;
const int SIGNDICT_FAIL = -1;

const int SIGNDICT_ERR_DUPLICATE_KEY = -2;
const int SIGNDICT_ERR_DISORDERED_KEY = -3;
const int SIGNDICT_ERR_DICT_FULL = -4;

const int SIGNDICT_ERR_NOT_FOUND = -2;

/**
 * @brief Create a new SignDict instance.
 *
 * @param size num of entries in dict. should be greater than zero.
 * @param prefix_width bytes of prefix used as index. should be in [0, 3]. 
 *                     Pass in 0 to let itself work out the optimal value.
 * @param value_width bytes of value. Current implementation supports up to 1024 bytes.
 *
 * @return 
 *   @li pointer to a new SignDict instance if success
 *   @li @c NULL if failed (memory allocation failed, invalid arguments, etc.)
 **/
SignDict_t* signdict_new(u_int size, u_int prefix_width, u_int value_width);

/**
 * @brief Delete SignDict instance and deallocated memory.
 *
 * @param dict SignDict instance to be deleted.
 *
 * @return 
 *   @li @c SIGNDICT_OK      if success
 *   @li @c SIGNDICT_FAIL    if failed
 **/
int signdict_delete(SignDict_t *dict);

/**
 * @brief Get value width of SignDict.
 *
 * @param dict pointer to SignDict instance.
 *
 * @return 
 *   @li value width of dict  if success
 *   @li @c SIGNDICT_FAIL     if failed
 **/
u_int signdict_value_width(const SignDict_t *dict);

/**
 * @brief Get dict size of SignDict.
 *
 * @param dict pointer to sSignDict instance.
 *
 * @return 
 *   @li size of dict     if success
 *   @li @c SIGNDICT_FAIL if failed
 **/
u_int signdict_size(const SignDict_t *dict);

/**
 * @brief Insert one a dict entry into SignDict. The @c sign[2] is key of the entry.
 *        @c dict->value_width_ bytes in @c value_buf is copied into dict.
 *
 * @param dict pointer to SignDict instance.
 * @param sign[2] 64bit sign of key.
 * @param value_buf pointer to value buffer.
 *
 * @return 
 *   @li @c SIGNDICT_OK                 on success
 *   @li @c SIGNDICT_FAIL               on general failure
 *   @li @c SIGNDICT_ERR_DUPLICATE_KEY  on key duplicated
 *   @li @c SIGNDICT_ERR_DISORDERED_KEY on key disordered 
 *   @li @c SIGNDICT_ERR_DICT_FULL      on dict is full
 *
 * @note  The key @b MUST be greater than last inserted key, i.e. dict entries 
 *        should be in ascending order of key.
 * @note  Caller should guarantee that the @c value_buf is at least as long as @c
 *        dict->value_width_.
 *
 * @attention No thread-safety guaranteed! @b NEVER attempt to build SignDict 
 *            within a multi-threading context.
 **/
int signdict_insert_one(SignDict_t *dict, const u_int sign[2], const u_char *value_buf);

/**
 * @brief Insert all dict entries into SignDict at a time.
 *
 * @param dict pointer to SignDict instance.
 * @param signs signs of dict entries that stored in sequence.
 * @param values fix-width values stored in sequnce.
 * @param count number of dict entries.
 *
 * @return 
 *   @li @c SIGNDICT_OK                 on success
 *   @li @c SIGNDICT_FAIL               on general failure
 *   @li @c SIGNDICT_ERR_DUPLICATE_KEY  on key duplicated
 *   @li @c SIGNDICT_ERR_DISORDERED_KEY on key disordered
 *   @li @c SIGNDICT_ERR_DICT_FULL      on dict is full
 *
 * @note  The key @b MUST be greater than last inserted key, i.e. dict entries 
 *        should be in ascending order of key.
 * @note  Caller should guarantee that the @c value_buf is at least as long as @c
 *        dict->value_width_.
 *
 * @attention No thread-safety guaranteed! @b NEVER attempt to build SignDict 
 *            within a multi-threading context.
 **/
int signdict_insert_batch(SignDict_t *dict, const u_int *signs, const u_char *values, u_int count);

/**
 * @brief Finalize insertion of dict entries. Should be called after all entries
 *        are inserted. No entry is allowed to be added any more.
 *
 * @param dict pointer to SignDict instance.
 *
 * @return 
 *   @li @c SIGNDICT_OK      on success
 *   @li @c SIGNDICT_FAIL    on failure
 **/
int signdict_finalize_insertion(SignDict_t *dict);

/**
 * @brief Search in Signdict for an dict entry given the sign of key. If found, 
 *        the value is copied into @c value_buf.
 *
 * @param dict pointer to SignDict instance.
 * @param sign[2] key of sign.
 * @param value_buf[out] buffer to store found value.
 *
 * @return 
 *   @li @c SIGNDICT_OK              on success
 *   @li @c SIGNDICT_FAIL            on general failure
 *   @li @c SIGNDICT_ERR_NOT_FOUND   on key not found
 *
 * @note  Caller should guarantee that the @c value_buf is at least as long as @c dict->value_width_
 * @note  This function is reentrant and is safe to use in multi-threading contexts.
 **/
int signdict_search(const SignDict_t *dict, const u_int sign[2], u_char *value_buf);

/**
 * @brief Dump SignDict to binary file.
 *
 * @param dict pointer to SignDict instance.
 * @param fp pointer of file to dump to.
 *
 * @return 
 *   @li @c SIGNDICT_OK      on success
 *   @li @c SIGNDICT_FAIL    on failure
 **/
int signdict_dump(const SignDict_t *dict, FILE *fp);

/**
 * @brief Load SignDict from binary file.
 *
 * @param fp pointer of file to load from.
 *
 * @return 
 *   @li pointer to SignDict instance     on success
 *   @li @c NULL                          on failure
 **/
SignDict_t* signdict_load(FILE *fp);

/**
 * @brief Decide if two SignDict instance is equal.
 *
 * @param lhs lhs SignDict instance.
 * @param rhs rhs SignDict instance.
 *
 * @return  
 *   @li @c 0    if two SignDict instance is equal
 *   @li @c -1   if is not equal
 *
 * @note  two SignDict is equal only if: @n
*    1. both pointers point to the same SignDict instance. @n
*    2. both pointers point to valid SignDict instance and all members equals to each other.
 **/
int signdict_is_equal(const SignDict_t *lhs, const SignDict_t *rhs);

#endif  //__SIGNDICT_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
