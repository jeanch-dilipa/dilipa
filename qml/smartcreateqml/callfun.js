.pragma library

function createqml(str,parentwindow)
{
    return Qt.createComponent(str).createObject(parentwindow);
}
