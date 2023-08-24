#include "msg.h"

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