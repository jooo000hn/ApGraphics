#ifndef _DELETEMACRO_H
#define _DELETEMACRO_H

// Defines
#define SafeRelease(x) {if (x){x->Release();x = nullptr;}}
#define SafeDelete(x) {if (x){delete x; x = nullptr;}}

#endif // !_DELETEMACRO_H
