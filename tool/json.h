#ifndef __JSON_H__
#define __JSON_H__
#include <iostream>
#include <functional>
using namespace std;
#include "cJSON.h"

typedef cJSON* json_t;
typedef function<bool(json_t)> json_cb_t;
class Json{
public:
    explicit Json(json_t jt);
    explicit Json(const char* jc);
    ~Json();

    /*数据查询*/
    json_t json();
    json_t json(const char* key);
    void show();
    const char* getCharPtr(const char* key);
    int getInt(const char* key);
    double getDouble(const char* key);
    static json_t json(json_t jt,const char* key);
    static void show(json_t jt);
    static const char* getCharPtr(json_t jt,const char* key);
    static int getInt(json_t jt,const char* key);
    static double getDouble(json_t jt,const char* key);

    static void traversalArr(json_t jt,json_cb_t cb);
    /*数据增添*/
    
    /*数据修改*/

private:
    json_t json_;
};

ostream& operator<<(ostream& cout,Json& json);

#endif