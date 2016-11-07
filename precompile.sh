#!/bin/sh
g++ -E -D _STALIB_ Templates.h | grep . | grep -v "^#" > templates.h
