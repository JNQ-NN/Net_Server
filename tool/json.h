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
    Json();
    explicit Json(json_t jt);
    explicit Json(char* jc);
    explicit Json(const char* jc);
    ~Json();

    /*数据查询*/
    json_t json();
    json_t json(const char* key);
    void show();
    const char* getCharPtr(const char* key);
    int getInt(const char* key);
    double getDouble(const char* key);
    bool getBool(const char* key);
    static json_t json(json_t jt,const char* key);
    static void show(json_t jt);
    static const char* getCharPtr(json_t jt,const char* key);
    static int getInt(json_t jt,const char* key);
    static double getDouble(json_t jt,const char* key);
    static bool getBool(json_t jt,const char* key);
    static void traversalArr(json_t jt,json_cb_t cb);

    /*数据增添*/
    void appendCharPtr(const char* key,const char* value);
    void appendStr(string key,string value);
    void appendInt(const char* key,int value);
    void appendDouble(const char* key,double value);
    void appendBool(const char* key,bool value);
    void appendArr(const char* key,vector<int>& arr);
    void appendArr(const char* key,vector<double>& arr);
    void appendArr(const char* key,vector<string>& arr);
    void appendArr(const char* key,vector<const char*>& arr);
    static void appendCharPtr(json_t jt,const char* key,const char* value);
    static void appendStr(json_t jt,string key,string value);
    static void appendInt(json_t jt,const char* key,int value);
    static void appendDouble(json_t jt,const char* key,double value);
    static void appendBool(json_t jt,const char* key,bool value);
    static void appendArr(json_t jt,const char* key,vector<int>& arr);
    static void appendArr(json_t jt,const char* key,vector<double>& arr);
    static void appendArr(json_t jt,const char* key,vector<string>& arr);
    static void appendArr(json_t jt,const char* key,vector<const char*>& arr);

    /*数据修改*/
    void modifyCharPtr(const char* key,const char* value);
    void modifyInt(const char* key,int value);
    void modifyDouble(const char* key,double value);
    void modifyArr(const char* key,vector<const char*> arr);
    void modifyArr(const char* key,vector<int> arr);
    void modifyArr(const char* key,vector<double> arr);
    static void modifyCharPtr(json_t jt,const char* key,const char* value);
    static void modifyInt(json_t jt,const char* key,int value);
    static void modifyDouble(json_t jt,const char* key,double value);
    static void modifyArr(json_t jt,const char* key,vector<const char*>& arr);
    static void modifyArr(json_t jt,const char* key,vector<int>& arr);
    static void modifyArr(json_t jt,const char* key,vector<double>& arr);
    
    /*数据序列化&反序列化*/
    char* serialization();
    void deserialization(const char* str);
    
    static void test();
private:
    json_t json_;

};

ostream& operator<<(ostream& cout,Json& json);

#endif