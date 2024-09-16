#include "json.h"

#define SET_NEXT_CHAR(ptr)      (ptr)++;
#define INDENTATION_CHAR        "--"
#define PRINT_NUMBER_FORMAT     "%.2f"

static int *indentation = NULL;

static void printIndentation(int counter) {
    int index = 0;
    while (index++ != counter) {
        printf(INDENTATION_CHAR);
    }
}

static void skip_whitspace(const char **ptr) {
    while (isspace(**ptr)) {
        (*ptr)++;
    }
}

JsonValue *parseJson(const char **json_ptr) {
    skip_whitspace(json_ptr);

    switch (**json_ptr) {
        case 'n':
            return parseNull(json_ptr);
        case 't':
        case 'f':
            return parseBool(json_ptr);
        case '\"':
            return parseString(json_ptr);
        case '[':
            return parseArray(json_ptr);
        case '{':
            return parseObject(json_ptr);
        default:
            if (isdigit(**json_ptr) || **json_ptr == '-') {
                return parseNumber(json_ptr);
            } else {
                // parse error handle
                return NULL;
            }
            break;
    }
}

JsonValue *parseNull(const char **json_ptr) {
    skip_whitspace(json_ptr);
    if (strncmp(*json_ptr, "null", 4) == 0) {
        JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
        value->type = JSON_NULL;
        *json_ptr += 4;
        return value;
    }
    return NULL;
}

JsonValue *parseBool(const char **json_ptr) {
    JsonValue *value = NULL;
    skip_whitspace(json_ptr);

    if (strncmp(*json_ptr, "true", 4) == 0) {
        value = (JsonValue *)malloc(sizeof(JsonValue));
        value->type = JSON_BOOLEAN;
        value->value.boolean = true;
        *json_ptr += 4;
    } else if (strncmp(*json_ptr, "false", 5) == 0) {
        value = (JsonValue *)malloc(sizeof(JsonValue));
        value->type = JSON_BOOLEAN;
        value->value.boolean = false;
        *json_ptr += 5;
    } else {
        return NULL;
    }
    return value;
}

JsonValue *parseNumber(const char **json_ptr) {
    char *end_parse = NULL;
    skip_whitspace(json_ptr);
    double number = strtod(*json_ptr, &end_parse);
    if (*json_ptr != end_parse) {
        JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
        value->type = JSON_NUMBER;
        value->value.number = number;
        *json_ptr = end_parse;
        return value;
    }
    return NULL;
}

JsonValue *parseString(const char **json_ptr) {
    skip_whitspace(json_ptr);

    if (**json_ptr == '\"') {
        (*json_ptr)++;
        const char *starting_str_address = *json_ptr;

        while ((**json_ptr != '\"') && (**json_ptr != '\0')) {
            (*json_ptr)++;
        }

        if (**json_ptr == '\"') {
            // allocate string memory
            size_t string_size = *json_ptr - starting_str_address;
            char *string_ptr =  (char *)malloc(sizeof(char)*(string_size + 1));
            strncpy(string_ptr, starting_str_address, string_size);
            string_ptr[string_size] = '\0';
            // allocate new json value
            JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
            value->type = JSON_STRING;
            value->value.string = string_ptr;

            (*json_ptr)++;
            return value;
        }
    }
    return NULL;
}

JsonValue *parseArray(const char **json_ptr) {
    skip_whitspace(json_ptr);
    if (**json_ptr == '[') {
        (*json_ptr)++;
        skip_whitspace(json_ptr);

        JsonValue *array = (JsonValue *)malloc(sizeof(JsonValue));
        array->type = JSON_ARRAY;
        array->value.array.count = 0;
        array->value.array.values = NULL;

        while ((**json_ptr != ']') && (**json_ptr != '\0')) {
            JsonValue *element = parseJson(json_ptr);

            if (element != NULL) {
                array->value.array.count += 1;
                array->value.array.values = realloc(array->value.array.values, (sizeof(JsonValue) * array->value.array.count));
                array->value.array.values[array->value.array.count - 1] = *element;
                free(element);
            } else {
                break;
            }

            skip_whitspace(json_ptr);
            if (**json_ptr == ',') {
                (*json_ptr)++;
            }
        }

        if (**json_ptr == ']') {
            (*json_ptr)++;
            return array;
        } else {
            freeJsonValue(array);
            free(array);
            return NULL;
        }
    }
    return NULL;
}

JsonValue *parseObject(const char **json_ptr) {
    skip_whitspace(json_ptr);

    if (**json_ptr == '{') {
        (*json_ptr)++;
        skip_whitspace(json_ptr);

        JsonValue *object = (JsonValue *)malloc(sizeof(JsonValue));
        object->type = JSON_OBJECT;
        object->value.object.count = 0;
        object->value.object.keys = NULL;
        object->value.object.values = NULL;

        // parse key and value
        while ((**json_ptr != '{') && (**json_ptr != '\0')) {
            JsonValue *key = parseString(json_ptr);

            if (key != NULL) {
                skip_whitspace(json_ptr);

                if (**json_ptr == ':') {
                    (*json_ptr)++;
                    JsonValue *value = parseJson(json_ptr);
                    
                    if (value != NULL) {
                        object->value.object.count++;
                        // add key
                        object->value.object.keys = realloc(object->value.object.keys, sizeof(JsonValue)*object->value.object.count);
                        object->value.object.keys[object->value.object.count - 1] = key->value.string;
                        // add value
                        object->value.object.values = realloc(object->value.object.values, sizeof(JsonValue)*object->value.object.count);
                        object->value.object.values[object->value.object.count - 1] = *value;
                        
                        free(value);
                        free(key);

                        skip_whitspace(json_ptr);
                        if (**json_ptr == ',') {
                            (*json_ptr)++;
                        }
                        continue;
                    }
                }
                // syntax error, not found value
                freeJsonValue(key);
                free(key);
                break;
            } else {
                break;
            }
        }
        // find object end char '}'
        if (**json_ptr == '}') {
            (*json_ptr)++;
            return object;
        } else {
            freeJsonValue(object);
            free(object);
            return NULL;
        }
    }
    return NULL;
}

void freeJsonValue(JsonValue *json_value) {
    if (json_value == NULL) {
        return;
    }

    switch (json_value->type) {
        case JSON_STRING:
            free(json_value->value.string);
            break;
        case JSON_ARRAY:
            for (size_t index=0;index<json_value->value.array.count;index++) {
                // truyền vào địa chỉ vùng nhớ được cấp phát cho json value
                freeJsonValue(&json_value->value.array.values[index]);
                // hoặc có thể truyền vào tham số như này
                // freeJsonValue(json_value->value.array.values + index);
            }
            free(json_value->value.array.values);
            break;
        case JSON_OBJECT:
            for (size_t index=0;index<json_value->value.object.count;index++) {
                free(json_value->value.object.keys[index]);
                freeJsonValue(&json_value->value.object.values[index]);
            }
            free(json_value->value.object.keys);
            free(json_value->value.object.values);
            break;
        default:
            break;
    }
}

void printJson(JsonValue* json_value) {
    if (json_value == NULL) {
        return;
    }

    switch (json_value->type) {
        case JSON_OBJECT:
            printJsonObject(json_value);
            break;
        case JSON_ARRAY:
            printJsonArray(json_value);
            break;
        case JSON_STRING:
            printJsonString(json_value);
            break;
        case JSON_NUMBER:
            printJsonNumber(json_value);
            break;
        case JSON_BOOLEAN:
            printJsonBoolean(json_value);
            break;
        case JSON_NULL:
            printJsonString(json_value);
            break;
    }
}

void printJsonObject(JsonValue* json_value) {
    if (json_value == NULL) {
        return;
    }

    size_t numObjects = json_value->value.object.count;
    for (size_t objectIndex=0;objectIndex<numObjects;objectIndex++) {

        if (objectIndex == 0) {
            if (indentation == NULL) {
                indentation = (int *)malloc(sizeof(int));
                *indentation = 0;
            } else {
                (*indentation)++;
                printf("\n");
            }
        }

        if (*indentation > 0) {
            printIndentation(*indentation);
        }

        printf("%s: ", json_value->value.object.keys[objectIndex]);
        printJson(&json_value->value.object.values[objectIndex]);
        if (json_value->value.object.values[objectIndex].type != JSON_OBJECT) {
            printf("\n");
        }
    }

    (*indentation)--;
    if (*indentation == 0) {
        free(indentation);
    }
}

void printJsonArray(JsonValue* json_value) {
    for (int i = 0; i < json_value->value.array.count; i++) {
        printf("\n");
        printIndentation(*indentation + 1);
        printJson(&json_value->value.array.values[i]);
    } 
}

void printJsonString(JsonValue* json_value) {
    printf("%s", json_value->value.string);
}

void printJsonNumber(JsonValue* json_value) {
    printf(PRINT_NUMBER_FORMAT, json_value->value.number);
}

void printJsonBoolean(JsonValue* json_value) {
    printf("%s", json_value->value.boolean ? "True" : "False");
}

void printJsonNull(JsonValue* json_value) {
    printf("%s", "Null");
}
