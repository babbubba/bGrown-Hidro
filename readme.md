## bGrown Hidro v1 alpha

### Componenti elettronici

#### Relays

##### SLA-05VDC-SL-C 

3 pezzi. 2 in modulo 2 canali (montabile su DIN) ed uno in modulo 1canale (montabile su DIN), entrambi alimentati 5V con opto accoppiatori sui canali.

Il modulo alimentato non assorbe praticamente nulla. La bobina eccitata assorbe circa 190 mA.

La bobina si attua con >= 2.6V.

Ho scelto questi perché reggono carichi da 30A a 220V quindi sufficienti per i carichi induttivi di ventole di riscaldamento o resistenze medio potenti.

##### SRD-05VDC-SL-C

4 pezzi montati su unica scheda modulo relay con opto accoppiatori.

Ogni bobina assorbe 75mA e regge carichi fino a 10A a 220V... in realtà lo useremo per la linea a 12V che attua le pompe peristaltiche.

N.B. Le bobine del modulo relays in questione si attuano quando il canale va a 0V (GND) quindi ricordarsi il segnale di LOW dall'ESP32.

### Somma dei carichi

| Componente                       | Q.ta | Assorb. Singolo (mA) | Assorb. Totale (mA/W) | Linea |
| -------------------------------- | ---- | -------------------- | --------------------- | ----- |
| Relay: SLA-05VDC-SL-C            | 3    | 190                  | 570mA/2.85W           | 5V    |
| Relay: SRD-05VDC-SL-C            | 4    | 75                   | 300mA/1.5W            | 5V    |
| Pompa Peristaltica: NKP-DCL-510Y | 4    | 630                  | 2520mA/30.2W          | 12V   |
|                                  |      |                      |                       |       |

