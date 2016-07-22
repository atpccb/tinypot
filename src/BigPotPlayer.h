#pragma once

#include "BigPotBase.h"
#include "BigPotMedia.h"
#include "BigPotUI.h"
#include "BigPotConv.h"
#include "BigPotConfig.h"
#include "BigPotSubtitle.h"

class BigPotPlayer : public BigPotBase
{
public:
    BigPotPlayer();
    BigPotPlayer(void* handle) : BigPotPlayer() { _handle = handle; }
    BigPotPlayer(char* s) : BigPotPlayer() { _filepath = getFilePath(s); }
    virtual ~BigPotPlayer();
private:
    std::string _drop_filename = "", _filepath;
    int _cur_time = 0;

    BigPotMedia* _media = nullptr;
    BigPotUI* _UI = nullptr;
    BigPotSubtitle* _subtitle = nullptr;

    int _w, _h;
    bool _run = true;

    std::string _sys_encode = "cp936", _BP_encode = "utf-8";
    int _cur_volume;
    int eventLoop();
    void* _handle;
    //int drawTex2();
    //int showTex2();
    //string getSysString(const string& str);
public:
    int beginWithFile(const std::string& filename);
    int init();
    void destroy();
    void openMedia(const std::string& filename);
    void closeMedia(const std::string& filename);

};



