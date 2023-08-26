#include "msg.h"


MsgNode::MsgNode(){
    msg_ = new char[0];
    msgMaxLen_ = 0;
    msgCurLen_ = 0;
}

MsgNode::MsgNode(size_t msgMaxLen):msgMaxLen_(msgMaxLen),msgCurLen_(0)
{
    msg_ = new char[msgMaxLen];
    memset(msg_,' ',msgMaxLen);
}

MsgNode::MsgNode(const char* msg,unsigned int msgMaxLen):msgMaxLen_(msgMaxLen){
    msg_ = new char[msgMaxLen];
    memcpy(msg_,msg,msgMaxLen);
    msgCurLen_ = strlen(msg);   
}

MsgNode::MsgNode(Json* jt){
    msg_ = jt->serialization();
    msgMaxLen_ = strlen(msg_);
    msgCurLen_ = strlen(msg_);
}

char* MsgNode::getMsg(){
    return msg_;
}

Json MsgNode::getJson(){
    Json json(msg_);
    return json;
}

/*
* @brief resize msg, 不保留原数据
*/
void MsgNode::resize(size_t newMsgMaxSize){
    delete[] msg_;
    msg_ = new char[newMsgMaxSize];
    msgMaxLen_ = newMsgMaxSize;
    msgCurLen_ = 0;
}

void MsgNode::msgClear(){
    memset(msg_,' ',msgMaxLen_);
    msgCurLen_ = 0;
}

size_t MsgNode::getMsgMaxLen(){
    return msgMaxLen_;
}

size_t MsgNode::getMsgCurLen(){
    return msgCurLen_;
}

/*
* 将消息封装成协议[消息头+消息体]
*/
string MSG::packing(char* msgBody){
    string msg="";
    size_t msgLen = MSGHEAD_LEN + strlen(msgBody)+1;
    char msgArr[msgLen];
    memset(msgArr,' ',msgLen);
    snprintf(msgArr,msgLen,"%10ld%s",msgLen-1-MSGHEAD_LEN,msgBody);
    msg = msgArr;
    return msg;
}

string MSG::packing(Json* json){
    return packing(json->serialization());
}