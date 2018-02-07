#include <doxygen.h>
#include <NexButton.h>
#include <NexCheckbox.h>
#include <NexConfig.h>
#include <NexCrop.h>
#include <NexDualStateButton.h>
#include <NexGauge.h>
#include <NexGpio.h>
#include <NexHardware.h>
#include <NexHotspot.h>
#include <NexNumber.h>
#include <NexObject.h>
#include <NexPage.h>
#include <NexPicture.h>
#include <NexProgressBar.h>
#include <NexRadio.h>
#include <NexRtc.h>
#include <NexScrolltext.h>
#include <NexSlider.h>
#include <NexText.h>
#include <NexTimer.h>
#include <Nextion.h>
#include <NexTouch.h>
#include <NexUpload.h>
#include <NexVariable.h>

// Arduino  -> Nextion
// Pino 5v  -> Vermelho
// Pino GND -> Preto
// Pino 0   -> azul
// Pino 1   -> Amarelo

#define dbSerial Serial

#define nexSerial Serial2

int32_t mls100 = 0;
int32_t mls10 = 0;
int32_t mls1 = 0;
int mls = 0;

int baias[10];

int c2 = 0; //c2 = 0: tela config ml
// c2 = 1: tela de configuração de amostras
//c2 = 2: sistema em processo



//________________________________Detecção de bandejas___________________________

const int bandeja0 =  22;
const int bandeja1 =  24;
const int bandeja2 =  26;
const int bandeja3 =  28;
const int bandeja4 =  30;
const int bandeja5 =  32;
const int bandeja6 =  34;
const int bandeja7 =  36;
const int bandeja8 =  38;
const int bandeja9 =  40;

NexPage config1 = NexPage(2, 0, "config1");
NexPage config2 = NexPage(3, 0, "config2");

//pagina inicial
NexButton b_iniciar = NexButton(1, 1, "b_iniciar");

//pagina config_1
//______________________________________________________________________________

NexButton config1_cont = NexButton(2, 1, "config1_cont");
NexButton config1_voltar = NexButton(2, 5, "config1_voltar");

NexButton mld3p = NexButton(2, 6, "mld3p");
NexButton mld3m = NexButton(2, 7, "mld3m");

NexButton mld2p = NexButton(2, 8, "mld2p");
NexButton mld2m = NexButton(2, 10, "mld2m");

NexButton mld1p = NexButton(2, 9, "mld1p");
NexButton mld1m = NexButton(2, 11, "mld1m");


NexText selecione = NexText(2, 13, "t0");

NexNumber ml0 = NexNumber(2, 2, "ml0");
NexNumber ml1 = NexNumber(2, 3, "ml1");
NexNumber ml2 = NexNumber(2, 4, "ml2");

//pagina config2
//____________________________________________________________________________________________________
//declarar baias
NexText baia0 = NexText(3, 11, "t0");
NexText baia1 = NexText(3, 12, "t1");
NexText baia2 = NexText(3, 13, "t2");
NexText baia3 = NexText(3, 14, "t3");
NexText baia4 = NexText(3, 15, "t4");
NexText baia5 = NexText(3, 16, "t5");
NexText baia6 = NexText(3, 17, "t6");
NexText baia7 = NexText(3, 18, "t7");
NexText baia8 = NexText(3, 19, "t8");
NexText baia9 = NexText(3, 20, "t9");

//declarar amostras
NexNumber n0 = NexNumber(3, 8, "n0");
NexNumber n1 = NexNumber(3, 9, "n1");
NexNumber n2 = NexNumber(3, 10, "n2");

//botões
//iniciar voltar
NexButton iniciar_p = NexButton(3, 21, "b0");

NexButton voltar1 = NexButton(3, 1, "b1");


//amostras
NexButton AmaisC = NexButton(3, 2, "b2");
NexButton AmenosC = NexButton(3, 5, "b3");

NexButton AmaisD = NexButton(3, 3, "b4");
NexButton AmenosD = NexButton(3, 6, "b6");

NexButton AmaisU = NexButton(3, 4, "b5");
NexButton AmenosU = NexButton(3, 7, "b7");

//baias disponiveis
NexText on0 = NexText(3, 22, "ba0");
NexText on1 = NexText(3, 23, "ba1");
NexText on2 = NexText(3, 24, "ba2");
NexText on3 = NexText(3, 25, "ba3");
NexText on4 = NexText(3, 26, "ba4");
NexText on5 = NexText(3, 27, "ba5");
NexText on6 = NexText(3, 28, "ba6");
NexText on7 = NexText(3, 29, "ba7");
NexText on8 = NexText(3, 30, "ba8");
NexText on9 = NexText(3, 31, "ba9");


//___________________________________________________________________________________________________________

NexTouch *nex_listen_list[] =
{
  &ml0, &ml1, &ml2,
  &on0, &on1, &on2, &on3, &on4, &on5, &on7, &on7, &on8, &on9,
  &baia0, &baia1, &baia2, &baia3, &baia4, &baia5, &baia6, &baia7, &baia8, &baia9,
  &AmaisC, &AmenosC, &AmaisD, &AmenosD, &AmaisU, &AmenosU,
  &voltar1, &iniciar_p,
  &mld3p, &mld3m,
  &mld2p, &mld2m,
  &mld1p, &mld1m,
  &selecione, &config1_cont,
  NULL
};


//____________________________________________________________________________________________________________
void doonup100(void *ptr) {
  uint32_t number;
  dbSerialPrintln("doonup100");
  ml0.getValue(&number);
  if (number < 9)
  {
    number += 1;
  }
  ml0.setValue(number);
}

void doondn100(void *ptr) {
  uint32_t number;
  dbSerialPrintln("doondn100");
  ml0.getValue(&number);
  if (number > 0)
  {
    number -= 1;
  }
  ml0.setValue(number);
}


void doonup10(void *ptr) {
  uint32_t number;
  dbSerialPrintln("doonup10");
  ml1.getValue(&number);
  if (number < 9)
  {
    number += 1;
  }
  ml1.setValue(number);
}

void doondn10(void *ptr) {
  uint32_t number;
  dbSerialPrintln("doondn10");
  ml1.getValue(&number);
  if (number > 0)
  {
    number -= 1;
  }
  ml1.setValue(number);
}


void doonup1(void *ptr) {
  uint32_t number;
  dbSerialPrintln("doonup1");
  ml2.getValue(&number);
  if (number < 9)
  {
    number += 1;
  }
  ml2.setValue(number);

}

void doondn1(void *ptr) {
  uint32_t number;
  dbSerialPrintln("doondn1");
  ml2.getValue(&number);
  if (number > 0)
  {
    number -= 1;
  }
  ml2.setValue(number);

}

//____________________________________________________________________________________________________________
void cont1(void *ptr) {
  ml0.getValue(&mls100);
  ml1.getValue(&mls10);
  ml2.getValue(&mls1);


  mls = mls100 * 100 + mls10 * 10 + mls1;

  if (mls == 0) {
    c2 = 0;
  }
  else {
    config2.show();
    c2 = 1;

  }
  dbSerialPrintln("cont1");
  dbSerialPrintln(mls);

}


//____________________________________________________________________________________________________________
void volt1(void *ptr) {
  c2 = 0;
  config1.show();

  dbSerialPrintln("voltar1");

}


void AP100(void *ptr) {
  if (c2 == 1) {
    uint32_t number100;
    dbSerialPrintln("AM100");
    n0.getValue(&number100);
    if (number100 < 3)
    {
      number100 += 1;
    }
    n0.setValue(number100);
    if (number100 == 3) {
      n1.setValue(0);
      n2.setValue(0);
    }
  }
}

void AM100(void *ptr) {
  if (c2 == 1) {
    uint32_t number100;
    dbSerialPrintln("AM100");
    n0.getValue(&number100);
    if (number100 > 0)
    {
      number100 -= 1;
    }
    n0.setValue(number100);
  }
}

void AP10(void *ptr) {
  if (c2 == 1) {
    uint32_t number100;
    n0.getValue(&number100);
    uint32_t number10;
    dbSerialPrintln("AP10");

    n1.getValue(&number10);
    if (number100 != 3) {
      if (number10 < 9)
      {
        number10 += 1;
      }
      n1.setValue(number10);
    }
  }
}

void AM10(void *ptr) {
  if (c2 == 1) {
    uint32_t number100;
    n0.getValue(&number100);
    uint32_t number10;
    dbSerialPrintln("AM10");

    n1.getValue(&number10);
    if (number100 != 3) {
      if (number10 > 0)
      {
        number10 -= 1;
      }
      n1.setValue(number10);
    }
  }
}

void AP1(void *ptr) {
  if (c2 == 1) {
    uint32_t number100;
    n0.getValue(&number100);
    uint32_t number1;
    dbSerialPrintln("AP1");

    n2.getValue(&number1);
    if (number100 != 3) {
      if (number1 < 9)
      {
        number1 += 1;
      }
      n2.setValue(number1);
    }
  }
}

void AM1(void *ptr) {
  if (c2 == 1) {
    uint32_t number100;
    n0.getValue(&number100);
    uint32_t number1;
    dbSerialPrintln("AM1");

    n2.getValue(&number1);
    if (number100 != 3) {
      if (number1 > 0)
      {
        number1 -= 1;
      }
      n2.setValue(number1);
    }
  }
}


//_________________________________________________________________________________________

void iniciar_processo(void *ptr) {
  //definir número de amostras
  uint32_t centena, dezena, unidade, total;
  n0.getValue(&centena);
  n1.getValue(&dezena);
  n2.getValue(&unidade);

  total = centena * 100 + dezena * 10 + unidade;

  dbSerialPrintln("Total de Amostras");
  dbSerialPrintln(total);

  int espera = dosagem(mls);
  dbSerialPrintln("Tempo de espera");
  dbSerialPrintln(espera);

  c2 = 2;


  if (digitalRead(bandeja0) == HIGH) {
    baia0.Set_background_crop_picc(5);
  }

  if (digitalRead(bandeja1) == HIGH) {
    baia1.Set_background_crop_picc(5);
  }

  if (digitalRead(bandeja2) == HIGH) {
    baia2.Set_background_crop_picc(5);
  }

  if (digitalRead(bandeja3) == HIGH) {
    baia3.Set_background_crop_picc(5);
  }

  if (digitalRead(bandeja4) == HIGH) {
    baia4.Set_background_crop_picc(5);
  }

  if (digitalRead(bandeja5) == HIGH) {
    baia5.Set_background_crop_picc(5);
  }

  if (digitalRead(bandeja6) == HIGH) {
    baia6.Set_background_crop_picc(5);
  }

  if (digitalRead(bandeja7) == HIGH) {
    baia7.Set_background_crop_picc(5);
  }

  if (digitalRead(bandeja8) == HIGH) {
    baia8.Set_background_crop_picc(5);
  }

  if (digitalRead(bandeja9) == HIGH) {
    baia9.Set_background_crop_picc(5);
  }

}


//__________________________________________________________________________________________



void setup() {
  //______________________________Bandejas como entradas____________________________________

  pinMode(bandeja0, INPUT);
  pinMode(bandeja1, INPUT);
  pinMode(bandeja2, INPUT);
  pinMode(bandeja3, INPUT);
  pinMode(bandeja4, INPUT);
  pinMode(bandeja5, INPUT);
  pinMode(bandeja6, INPUT);
  pinMode(bandeja7, INPUT);
  pinMode(bandeja8, INPUT);
  pinMode(bandeja9, INPUT);

  //_________________________________________________________________________________________

  nexInit();
  dbSerial.print("setup done");


  voltar1.attachPop(volt1, &voltar1);

  AmaisC.attachPop(AP100, &AmaisC);
  AmenosC.attachPop(AM100, &AmenosC);

  AmaisD.attachPop(AP10, &AmaisD);
  AmenosD.attachPop(AM10, &AmenosD);

  AmaisU.attachPop(AP1, &AmaisU);
  AmenosU.attachPop(AM1, &AmenosU);


  mld3p.attachPop(doonup100, &mld3p);
  mld3m.attachPop(doondn100, &mld3m);
  mld2p.attachPop(doonup10, &mld2p);
  mld2m.attachPop(doondn10, &mld2m);
  mld1p.attachPop(doonup1, &mld1p);
  mld1m.attachPop(doondn1, &mld1m);

  config1_cont.attachPop(cont1, &config1_cont);
  iniciar_p.attachPop(iniciar_processo, &iniciar_processo);
}



//_______________________________________________________________________________________________________________
void loop() {
  nexLoop(nex_listen_list);


  int Band0Ocupada, Band1Ocupada, Band2Ocupada, Band3Ocupada, Band4Ocupada;
  int Band5Ocupada, Band6Ocupada, Band7Ocupada, Band8Ocupada, Band9Ocupada;

  if (c2 == 1 || c2==2) {
    if (digitalRead(bandeja0) == HIGH) {
      baia0.Set_background_crop_picc(5);
      Band0Ocupada = 1;
    }
    else {
      baia0.Set_background_crop_picc(7);
      Band0Ocupada = 0;
    }

    if (digitalRead(bandeja1) == HIGH) {
      baia1.Set_background_crop_picc(5);
      Band1Ocupada = 1;
    }
    else {
      baia1.Set_background_crop_picc(7);
      Band1Ocupada = 0;
    }

    if (digitalRead(bandeja2) == HIGH) {
      baia2.Set_background_crop_picc(5);
      Band2Ocupada = 1;
    }
    else {
      baia2.Set_background_crop_picc(7);
      Band2Ocupada = 0;
    }

    if (digitalRead(bandeja3) == HIGH) {
      baia3.Set_background_crop_picc(5);
      Band3Ocupada = 1;
    }
    else {
      baia3.Set_background_crop_picc(7);
      Band3Ocupada = 0;
    }

    if (digitalRead(bandeja4) == HIGH) {
      baia4.Set_background_crop_picc(5);
      Band4Ocupada = 1;
    }
    else {
      baia4.Set_background_crop_picc(7);
      Band4Ocupada = 0;
    }

    if (digitalRead(bandeja5) == HIGH) {
      baia5.Set_background_crop_picc(5);
      Band5Ocupada = 1;
    }
    else {
      baia5.Set_background_crop_picc(7);
      Band5Ocupada = 0;
    }

    if (digitalRead(bandeja6) == HIGH) {
      baia6.Set_background_crop_picc(5);
      Band6Ocupada = 1;
    }
    else {
      baia6.Set_background_crop_picc(7);
      Band6Ocupada = 0;
    }

    if (digitalRead(bandeja7) == HIGH) {
      baia7.Set_background_crop_picc(5);
      Band7Ocupada = 1;
    }
    else {
      baia7.Set_background_crop_picc(7);
      Band7Ocupada = 0;
    }

    if (digitalRead(bandeja8) == HIGH) {
      baia8.Set_background_crop_picc(5);
      Band8Ocupada = 1;
    }
    else {
      baia8.Set_background_crop_picc(7);
      Band8Ocupada = 0;
    }

    if (digitalRead(bandeja9) == HIGH) {
      baia9.Set_background_crop_picc(5);
      Band9Ocupada = 1;
    }
    else {
      baia9.Set_background_crop_picc(7);
      Band9Ocupada = 0;
    }
    int baias[10] = {Band0Ocupada,
                     Band1Ocupada,
                     Band2Ocupada,
                     Band3Ocupada,
                     Band4Ocupada,
                     Band5Ocupada,
                     Band6Ocupada,
                     Band7Ocupada,
                     Band8Ocupada,
                     Band9Ocupada
                    };

    //Baias disponíveis


    for (int i = 0; i < 10; i++) {
      dbSerialPrintln(baias[i]);
    }
  }
}



int ler_bandejas() {


}


int dosagem(int ml) {
  // Determina o delay de dosagem de cada amostra
  int tempo, tml;
  tml = 10; //tempo em milissegundos necessarios para o fluxo de 1ml

  tempo = ml * tml; //Calcula o tempo de dosagem
  return tempo;
}



