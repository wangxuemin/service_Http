#!/bin/sh

iconv -f GB18030 -t UTF-8 -o tmp $1
mv tmp $1
