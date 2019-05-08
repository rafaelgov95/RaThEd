//
// Created by rafael on 10/04/19.
//

#ifndef RATHED_UTIL_H
#define RATHED_UTIL_H

#include <fstream>
#include <model.pb.h>
#include "iostream"
#include "vector"
#include "string"

struct CompareHash {
    CompareHash(const std::string val) : val_(val) {}

    bool operator()(const std::pair<std::string, std::string > &element) const {
        return val_ == element.first;
    }

private:
    std::string val_;
};

#ifdef __linux__
#include <unistd.h>
#endif
#ifdef __WIN32__
#include <windows.h>
#endif

static void mySleep(int sleepMs)
{
#ifdef __linux__
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef  __WIN32__
    Sleep(sleepMs);
#endif
}
struct CompareHashPeer {
    CompareHashPeer(const std::string val) : val_(val) {}

    bool operator()(const std::pair<std::string, std::vector<std::string >> &element) const {
        return val_ == element.first;
    }

private:
    std::string val_;
};

static void error(char *message) {
    perror(message);
    exit(1);
}
struct ComparableBuffer{
    explicit ComparableBuffer(rathed::Datagrama &data):data(data){}
    rathed::Datagrama data;
    bool operator <(ComparableBuffer const& other)const{return data.packnumber()<other.data.packnumber();}
};

static rathed::Datagrama DataGrama(int type, int32_t packNumber,std::string bytes) {
    rathed::Datagrama new_data;
    new_data.set_type(static_cast<rathed::DatagramaType>(type));
    new_data.set_packnumber(packNumber);
    new_data.set_data(bytes);
    return new_data;

};

static void *DataGramaSerial (rathed::Datagrama datagrama) {
size_t size = datagrama.ByteSizeLong();
void *buffer = malloc(size);
datagrama.SerializeToArray(buffer, size);
return buffer;
}

static long MyTempMS() {
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );
    return ms.count();
}

//std::streampos fileSize( const char* filePath ){
//
//    std::streampos fsize = 0;
//    std::ifstream file( filePath, std::ios::binary );
//
//    fsize = file.tellg();
//    file.seekg( 0, std::ios::end );
//    fsize = file.tellg() - fsize;
//    file.close();
//
//    return fsize;
//}
static const std::vector<std::string> my_split(const std::string& s, const char& c)
{
    std::string buff{""};
    std::vector<std::string> v;

    for(auto n:s)
    {
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}



#endif //RATHED_UTIL_H
