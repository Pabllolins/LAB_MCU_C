#ifndef _MEUPWM_H
    #define _MEUPWM_H

#include <Arduino.h>

    class meupwm {

        private:

        public:
          meupwm(int pino, long tempo);
          void variacao();      
    };
#endif