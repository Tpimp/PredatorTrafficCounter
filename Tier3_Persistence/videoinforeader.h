#ifndef VIDEOINFOREADER_H
#define VIDEOINFOREADER_H
#include <QHash>
class VideoInfoReader
{
public:
    static QString readVideoInfo(QString video_info_filepath);


private:
    VideoInfoReader();
};

#endif // VIDEOINFOREADER_H
