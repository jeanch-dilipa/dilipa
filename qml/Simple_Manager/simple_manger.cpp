#include "simple_manger.h"

Simple_Manger::Simple_Manger()
{
    connect(this,&Simple_Manger::signal_selectregion,&sqlite,&SqlLiteMake::sqllite_select);
    connect(&sqlite,&SqlLiteMake::signal_returnregionlist,this,&Simple_Manger::signal_returnregionlist);
}
