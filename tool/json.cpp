#include "json.h"

Json::Json(json_t jt){
    json_ = jt;
}

/*
 @json解析，将字符串解析成JSON
*/
Json::Json(const char* jc){
    json_ = cJSON_Parse(jc);
}

Json::~Json(){
    if(json_){
        delete json_;
        json_ = nullptr;
    }
}

json_t Json::json(){
    return json_;
}

json_t Json::json(const char* key){
    return json(json_,key);
}

void Json::show(){
    return show(json_);
}

const char* Json::getCharPtr(const char* key){
    return getCharPtr(json_,key);
}

int Json::getInt(const char* key){
    return getInt(json_,key);
}

double Json::getDouble(const char* key){
    return getDouble(json_,key);
}

json_t Json::json(json_t jt,const char* key){
    return (jt && jt->type == cJSON_Object)?cJSON_GetObjectItem(jt,key):nullptr;
}

void Json::show(json_t jt){
    cout<<cJSON_Print(jt)<<endl;
}

const char* Json::getCharPtr(json_t jt,const char* key){
    json_t j = json(jt,key);
    return (j && j->type==cJSON_String)?j->valuestring:nullptr;
}

int Json::getInt(json_t jt,const char* key){
    json_t j = json(jt,key);
    return (j && j->type==cJSON_Number)?j->valueint:0;
}

double Json::getDouble(json_t jt,const char* key){
    json_t j = json(jt,key);
    return (j && j->type==cJSON_Number)?j->valuedouble:0;
}

void Json::traversalArr(json_t jt,json_cb_t cb){
    if(jt == nullptr) return;
    if(jt->type != cJSON_Array){
        cb(jt);
    }else{
        int arrLength = cJSON_GetArraySize(jt);
        for(int i = 0;i<arrLength;i++){
            json_t arr_ptr = cJSON_GetArrayItem(jt,i);
            if(cb(jt)) return ;
        }
    }
}

ostream& operator<<(ostream& cout,Json& json){
    cout<<cJSON_Print(json.json());
    return cout;
}