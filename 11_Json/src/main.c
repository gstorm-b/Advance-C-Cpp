#include <stdio.h>
#include <stdint.h>
#include "json.h"

int main(void) {

    const char* json_str = "{"
                    "\"1001\":{"
                        "\"SoPhong\":3,"
                        "\"NguoiThue\":{"
                        "\"Ten\":\"Nguyen Van A\","
                        "\"CCCD\":\"1920517781\","
                        "\"Tuoi\":26,"
                        "\"ThuongTru\":{"
                            "\"Duong\":\"73 Ba Huyen Thanh Quan\","
                            "\"Phuong_Xa\":\"Phuong 6\","
                            "\"Tinh_TP\":\"Ho Chi Minh\""
                        "}"
                        "},"
                        "\"SoNguoiO\":{"
                        "\"1\":\"Nguyen Van A\","
                        "\"2\":\"Nguyen Van B\","
                        "\"3\":\"Nguyen Van C\""
                        "},"
                        "\"TienDien\": [24, 56, 98],"
                        "\"TienNuoc\":30.000"
                    "},"
                    "\"1002\":{"
                        "\"SoPhong\":5,"
                        "\"NguoiThue\":{"
                        "\"Ten\":\"Phan Hoang Trung\","
                        "\"CCCD\":\"012345678912\","
                        "\"Tuoi\":24,"
                        "\"ThuongTru\":{"
                            "\"Duong\":\"53 Le Dai Hanh\","
                            "\"Phuong_Xa\":\"Phuong 11\","
                            "\"Tinh_TP\":\"Ho Chi Minh\""
                        "}"
                        "},"
                        "\"SoNguoiO\":{"
                        "\"1\":\"Phan Van Nhat\","
                        "\"2\":\"Phan Van Nhi\","
                        "\"2\":\"Phan Van Tam\","
                        "\"3\":\"Phan Van Tu\""
                        "},"
                        "\"TienDien\":23.000,"
                        "\"TienNuoc\":40.000"
                    "}"
                    "}";

    JsonValue *json_parsed = parseJson(&json_str);
    printJson(json_parsed);
    freeJsonValue(json_parsed);


    // test array
    // const char *test_array = "[10, 20 ,30, 40, 100]";
    // JsonValue *value_array = parseArray(&test_array);
    // if (value_array) {
    //     size_t array_size = value_array->value.array.count;
    //     for(int index=0;index<array_size;index++) {
    //         printf("%f", value_array->value.array.values[index].value.number);
    //     }
    // }

    // test string
    // const char *test_string = "  \"hello world!\": 128932";
    // JsonValue *value_string = parseString(&test_string);
    // if (value_string) {
    //     printf("%s", value_string->value.string);
    // }

    // test number
    // const char *test_number = "  -0.001, adcsad";
    // JsonValue *value_number = parseNumber(&test_number);
    // if (value_number) {
    //     printf("%f", value_number->value.number);
    // }

    // test null
    // const char *test_null = "  null";
    // JsonValue *value_null = parseNull(&test_null);
    // printf("%s", (value_null->type == JSON_NULL) ? "Is Null" : "Not Null");

    // test bool
    // const char *test_bool = "false";
    // JsonValue *value_bool = parseBool(&test_bool);
    // printf("%d", value_bool->value.boolean);

    return 0;
}