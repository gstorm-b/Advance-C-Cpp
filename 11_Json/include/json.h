#ifndef JSON_H
#define JSON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>

#define NULL_STRING     "null"

#define _SET_NEXT_CHAR(pointer)     (pointer)++;

typedef enum {
    JSON_NULL,
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JsonType;

typedef struct JsonValue {
    JsonType type;
    union {
        int boolean;
        double number;
        char *string;
        struct {
            struct JsonValue *values;
            size_t count;
        } array;
        struct {
            char **keys;
            struct JsonValue *values;
            size_t count;
        } object;
    } value;
} JsonValue;

JsonValue *parseJson(const char **json_ptr);
JsonValue *parseNull(const char **json_ptr);
JsonValue *parseBool(const char **json_ptr);
JsonValue *parseNumber(const char **json_ptr);
JsonValue *parseString(const char **json_ptr);
JsonValue *parseArray(const char **json_ptr);
JsonValue *parseObject(const char **json_ptr);
void freeJsonValue(JsonValue *json_value);
void printJson(JsonValue* json_value);
void printJsonObject(JsonValue* json_value);
void printJsonArray(JsonValue* json_value);
void printJsonString(JsonValue* json_value);
void printJsonNumber(JsonValue* json_value);
void printJsonBoolean(JsonValue* json_value);
void printJsonNull(JsonValue* json_value);

#endif