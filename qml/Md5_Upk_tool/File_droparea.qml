import QtQuick 2.0

DropArea
{
    anchors.fill: parent

    onDropped:
    {
        if(drop.hasUrls)
        {
            for(var i=0;i<drop.urls.length;i++)
            {
                fileio.isfilefilter(drop.urls[i])
            }
        }
    }
}
