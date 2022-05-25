#include "state.h"

void State1::Do2(){m_context->SetState(new State3(new QString("state3")));}
