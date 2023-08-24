#include "json.h"

Json::Json(){
    json_ = nullptr;
    json_ = cJSON_CreateObject();
}

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

/*
 * json数组遍历
*/
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

void Json::appendCharPtr(const char* key,const char* value){
    appendCharPtr(json_,key,value);
}

void Json::appendInt(const char* key,int value){
    appendInt(json_,key,value);
}

void Json::appendDouble(const char* key,double value){
    appendDouble(json_,key,value);
}

void Json::appendArr(const char* key,vector<int>& arr){
    appendArr(json_,key,arr);
}

void Json::appendArr(const char* key,vector<double>& arr){
    appendArr(json_,key,arr);
}

void Json::appendArr(const char* key,vector<const char*>& arr){
    appendArr(json_,key,arr);
}

void Json::appendCharPtr(json_t jt,const char* key,const char* value){
    cJSON_AddStringToObject(jt,key,value);
}

void Json::appendInt(json_t jt,const char* key,int value){
    cJSON_AddNumberToObject(jt,key,value);
}

void Json::appendDouble(json_t jt,const char* key,double value){
    cJSON_AddNumberToObject(jt,key,value);
}

void Json::appendArr(json_t jt,const char* key,vector<int>& arr){
    json_t tempArr = nullptr;
    tempArr = cJSON_CreateArray();
    for(auto &a:arr){
        cJSON_AddItemToArray(tempArr,cJSON_CreateNumber(a));
    }
    cJSON_AddItemToObject(jt,key,tempArr);
}

void Json::appendArr(json_t jt,const char* key,vector<double>& arr){
    json_t tempArr = nullptr;
    tempArr = cJSON_CreateArray();
    for(auto &a:arr){
        cJSON_AddItemToArray(tempArr,cJSON_CreateNumber(a));
    }
    cJSON_AddItemToObject(jt,key,tempArr);
}

void Json::appendArr(json_t jt,const char* key,vector<const char*>& arr){
    json_t tempArr = nullptr;
    tempArr = cJSON_CreateArray();
    for(auto &a:arr){
        cJSON_AddItemToArray(tempArr,cJSON_CreateString(a));
    }
    cJSON_AddItemToObject(jt,key,tempArr);
}

void Json::modifyCharPtr(const char* key,const char* value){
    modifyCharPtr(json_,key,value);
}

void Json::modifyInt(const char* key,int value){
    modifyInt(json_,key,value);
}

void Json::modifyDouble(const char* key,double value){
    modifyDouble(json_,key,value);
}

void Json::modifyArr(const char* key,vector<const char*> arr){
    modifyArr(json_,key,arr);
}

void Json::modifyArr(const char* key,vector<int> arr){
    modifyArr(json_,key,arr);
}

void Json::modifyArr(const char* key,vector<double> arr){
    modifyArr(json_,key,arr);
}

/*
 *覆盖式修改
*/
void Json::modifyCharPtr(json_t jt,const char* key,const char* value){
    json_t j = json(jt,key);
    if(j && j->type==cJSON_String){
        cJSON_ReplaceItemInObjectCaseSensitive(jt,key,cJSON_CreateString(value));
    }
}

/*
 *覆盖式修改
*/
void Json::modifyInt(json_t jt,const char* key,int value){
    json_t j = json(jt,key);
    if(j && j->type==cJSON_Number){
        cJSON_ReplaceItemInObject(jt,key,cJSON_CreateNumber(value));
    }
}

/*
 *覆盖式修改
*/
void Json::modifyDouble(json_t jt,const char* key,double value){
    json_t j = json(jt,key);
    if(j && j->type==cJSON_Number){
        cJSON_ReplaceItemInObject(jt,key,cJSON_CreateNumber(value));
    }
}

/*
 *覆盖式修改
*/
void Json::modifyArr(json_t jt,const char* key,vector<const char*>& arr){
    json_t j = json(jt,key);
    if(j && j->type==cJSON_Array){
        json_t tempArr = nullptr;
        tempArr = cJSON_CreateArray();
        for(auto& a:arr){
           cJSON_AddItemToArray(tempArr,cJSON_CreateString(a));
        }
        cJSON_ReplaceItemInObject(jt,key,tempArr);  
    }
}

/*
 *覆盖式修改
*/
void Json::modifyArr(json_t jt,const char* key,vector<int>& arr){
    json_t j = json(jt,key);
    if(j && j->type==cJSON_Array){
        json_t tempArr = nullptr;
        tempArr = cJSON_CreateArray();
        for(auto& a:arr){
           cJSON_AddItemToArray(tempArr,cJSON_CreateNumber(a));
        }
        cJSON_ReplaceItemInObject(jt,key,tempArr);  
    }
}

/*
 *覆盖式修改
*/
void Json::modifyArr(json_t jt,const char* key,vector<double>& arr){
    json_t j = json(jt,key);
    if(j && j->type==cJSON_Array){
        json_t tempArr = nullptr;
        tempArr = cJSON_CreateArray();
        for(auto& a:arr){
           cJSON_AddItemToArray(tempArr,cJSON_CreateNumber(a));
        }
        cJSON_ReplaceItemInObject(jt,key,tempArr);  
    }
}

char* Json::serialization(){
    return cJSON_Print(json_);
}

void Json::deserialization(const char* str){
    json_ = cJSON_Parse(str);
}

void Json::test(){
    Json j;
    j.appendCharPtr("str","string");
    j.appendInt("NumInt",666);
    j.appendDouble("NumDouble",6.6);
    vector<int> v{1,2,3};
    j.appendArr("Arr1",v);
    vector<double> vv{1.1,2.2,3.3};
    j.appendArr("Arr2",vv);
    vector<const char*> vvv{"a1","a2","a3"};
    j.appendArr("Arr3",vvv);
    j.show();
    j.modifyCharPtr("str","charptr");
    j.modifyInt("NumInt",888);
    j.modifyDouble("NumDouble",6.6);
    vector<int> vi{10,20,30,40,50};
    vector<double> vvi{11.1,22.2,33.3,44.4,55.5};
    vector<const char*> vvvi{"aa1","aa2","aa3","aa4","aa5"};
    j.modifyArr("Arr1",vi);
    j.modifyArr("Arr2",vvi);
    j.modifyArr("Arr3",vvvi);
    j.show();
}

ostream& operator<<(ostream& cout,Json& json){
    cout<<cJSON_Print(json.json());
    return cout;
}