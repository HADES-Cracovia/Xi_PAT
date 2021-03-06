#include <iostream>
using namespace std;

class FWPad {
   int id;
   int classId;
   std::vector<FWPad*> pads; 
   std::vector<FWPad*>::iterator padsIt; 

public:
   FWPad(int i) : id(i), ptrHit(0) 
   {
      classId = (id < 144) ? 0 : (id < 208) ? 1 : 2;
   }
   ~FWPad() {}

   void addPad( FWPad *p ) { pads.push_back( p ); }

// ----------------------------------------------------------------------------
// ============================================================================
   bool isNext(int i) 
   {
      padsIt = pads.begin();
      while ( padsIt != pads.end() ) 
      { 
         if (*padsIt->getId() == i) return true;
         ++padsIt;
      }
    return false;
   }

   int getId() const { return id; }
   int getClassId() const { return classId; }
   void setId(int i) { id = i; }
   void setClassId(int c) { classId = c; }
   FWPad* getFWPad() { return this; }
};

class FWDetector {

std::vector<FWPad*> pads;
std::vector<FWPad*>::iterator padsIt;

public:
   FWDetector() 
   {
      // first we build the detector pads
      for (int i=0; i<273; ++i) 
      {
         pads.push_back( new FWPad(i) );
      }
      // then we create the list of neighbouring pads
      for (int i=0; i<273; ++i) 
      {
          for (int j=0; j<9; ++j) 
          {
              if (neighbours[i][j] != 0)
              {
                 pads[i]->addPad( pads[i][j] );
              }
          }
      }
   }
   ~FWDetector() { for (padsIt= pads.begin(); padsIt!=pads.end(); ++padsIt) delete *padsIt; }

   bool isNext(int mainhit, int nexthit)
   {
      return pads[ mainhit ]->isNext( nexthit );
   }

private:

   int neighbours[273][9]={
            {12,	1,	165,	156,	13,	155,	0,	0,	0},	
            {13,	2,	156,	12,	14,	157,	0,	0,	0},	
            {14,	3,	157,	1,	13,	15,	156,	0,	0},	
            {15,	4,	157,	2,	16,	158,	14,	0,	0},	
            {16,	5,	158,	3,	17,	157,	15,	0,	0},	
            {17,	6,	158,	4,	18,	159,	16,	0,	0},	
            {18,	7,	159,	5,	19,	158,	17,	0,	0},	
            {19,	8,	159,	6,	20,	160,	159,	18,	0},	
            {20,	9,	160,	7,	21,	159,	19,	0,	0},	
            {21,	10,	160,	8,	22,	161,	20,	0,	0},	
            {22,	11,	161,	9,	23,	160,	21,	0,	0},	
            {23,	166,	161,	10,	162,	22,	0,	0,	0},	
            {24,	13,	0,	165,	25,	1,	169,	0,	0},	
            {25,	14,	1,	12,	26,	2,	0,	24,	0},	
            {26,	15,	2,	13,	27,	3,	1,	25,	0},	
            {27,	16,	3,	14,	28,	4,	2,	26,	0},	
            {28,	17,	4,	15,	29,	5,	3,	27,	0},	
            {29,	18,	5,	16,	30,	6,	4,	28,	0},	
            {30,	19,	6,	17,	31,	7,	5,	29,	0},	
            {31,	20,	7,	18,	32,	8,	6,	30,	0},	
            {32,	21,	8,	19,	33,	9,	7,	31,	0},	
            {33,	22,	9,	20,	34,	10,	8,	32,	0},	
            {34,	23,	10,	21,	35,	11,	9,	33,	0},	
            {35,	166,	11,	22,	170,	10,	34,	0,	0},	
            {36,	25,	12,	169,	37,	13,	165,	0,	0},	
            {37,	26,	13,	24,	38,	14,	12,	36,	0},	
            {38,	27,	14,	25,	39,	15,	13,	37,	0},	
            {39,	28,	15,	26,	40,	16,	14,	38,	0},	
            {40,	29,	16,	27,	41,	17,	15,	39,	0},	
            {41,	30,	17,	28,	42,	18,	16,	40,	0},	
            {42,	31,	18,	29,	43,	19,	17,	41,	0},	
            {43,	32,	19,	30,	44,	20,	18,	42,	0},	
            {44,	33,	20,	31,	45,	21,	19,	31,	0},	
            {45,	34,	21,	32,	46,	22,	20,	44,	0},	
            {46,	35,	22,	33,	47,	23,	21,	45,	0},	
            {47,	170,	23,	34,	166,	22,	46,	0,	0},	
            {48,	37,	24,	169,	49,	25,	173,	0,	0},	
            {49,	38,	25,	36,	50,	26,	24,	48,	0},	
            {50,	39,	26,	37,	51,	27,	25,	49,	0},	
            {51,	40,	27,	38,	52,	28,	26,	50,	0},	
            {52,	41,	28,	39,	53,	29,	27,	51,	0},	
            {53,	42,	29,	40,	54,	30,	28,	52,	0},	
            {54,	43,	30,	41,	55,	31,	29,	53,	0},	
            {55,	44,	31,	42,	56,	32,	30,	54,	0},	
            {56,	45,	32,	43,	57,	33,	31,	55,	0},	
            {57,	46,	33,	44,	58,	34,	32,	56,	0},	
            {58,	47,	34,	45,	59,	35,	33,	57,	0},	
            {59,	170,	35,	46,	174,	34,	58,	0,	0},	
            {60,	49,	36,	173,	61,	37,	169,	0,	0},	
            {61,	50,	37,	48,	62,	38,	36,	60,	0},	
            {62,	51,	38,	49,	63,	39,	37,	61,	0},	
            {63,	52,	39,	50,	64,	40,	38,	62,	0},	
            {64,	53,	40,	51,	41,	39,	63,	0,	0},	
            {54,	41,	52,	42,	40,	64,	0,	0,	0},	
            {55,	42,	53,	67,	43,	41,	0,	0,	0},	
            {67,	56,	43,	54,	68,	44,	42,	0,	0},	
            {68,	57,	44,	55,	69,	45,	43,	67,	0},	
            {69,	58,	45,	56,	70,	46,	44,	68,	0},	
            {70,	59,	46,	57,	71,	47,	45,	69,	0},	
            {71,	174,	47,	58,	170,	46,	70,	0,	0},	
            {72,	61,	48,	173,	177,	73,	49,	0,	0},	
            {73,	62,	49,	60,	74,	50,	48,	72,	0},	
            {74,	63,	50,	61,	75,	51,	49,	73,	0},	
            {75,	64,	51,	62,	76,	52,	50,	74,	0},	
            {76,	52,	63,	53,	51,	75,	0,	0,	0},	
            {0,	0,	0,	0,	0,	0,	0,	0,	0},	
            {0,	0,	0,	0,	0,	0,	0,	0,	0},	
            {79,	68,	55,	80,	56,	54,	0,	0,	0},	
            {80,	69,	56,	67,	81,	57,	55,	79,	0},	
            {81,	70,	57,	68,	82,	58,	56,	80,	0},	
            {82,	71,	58,	69,	83,	59,	57,	81,	0},	
            {83,	174,	59,	70,	178,	58,	82,	0,	0},	
            {84,	73,	60,	177,	85,	61,	173,	0,	0},	
            {85,	74,	61,	72,	86,	62,	60,	84,	0},	
            {86,	75,	62,	73,	87,	63,	61,	85,	0},	
            {87,	76,	63,	74,	88,	64,	62,	86,	0},	
            {88,	64,	75,	89,	63,	87,	0,	0,	0},	
            {0,	0,	0,	0,	0,	0,	0,	0,	0},	
            {0,	0,	0,	0,	0,	0,	0,	0,	0},	
            {91,	80,	67,	92,	68,	90,	0,	0,	0},	
            {92,	81,	68,	79,	93,	69,	67,	91,	0},	
            {93,	82,	69,	80,	94,	70,	68,	92,	0},	
            {94,	83,	70,	81,	95,	71,	69,	93,	0},	
            {95,	178,	71,	82,	174,	70,	94,	0,	0},	
            {96,	85,	72,	177,	97,	73,	181,	0,	0},	 
            {97,	86,	73,	84,	98,	74,	72,	96,	0},	
            {98,	87,	74,	85,	99,	75,	73,	97,	0},	
            {99,	88,	75,	86,	100,	76,	74,	98,	0},	
            {100,	89,	76,	87,	101,	75,	99,	0,	0},	
            {101,	90,	88,	102,	76,	100,	0,	0,	0},	
            {102,	91,	89,	103,	79,	101,	0,	0,	0},	
            {103,	92,	79,	90,	104,	80,	102,	0,	0},	
            {104,	93,	80,	91,	105,	81,	79,	103,	0},	
            {105,	94,	81,	92,	106,	82,	80,	104,	0},	
            {106,	95,	82,	93,	107,	83,	81,	105,	0},	
            {107,	178,	83,	94,	182,	82,	106,	0,	0},	
            {108,	97,	84,	181,	109,	85,	177,	0,	0},	
            {109,	98,	85,	96,	110,	86,	84,	108,	0},	
            {110,	99,	86,	97,	111,	87,	85,	109,	0},	
            {111,	100,	87,	98,	112,	88,	86,	110,	0},	
            {112,	101,	88,	99,	113,	89,	87,	111,	0},	
            {113,	102,	89,	100,	114,	90,	88,	112,	0},	
            {114,	103,	90,	101,	115,	91,	89,	113,	0},	
            {115,	104,	91,	102,	116,	92,	90,	114,	0},	
            {116,	105,	92,	103,	117,	93,	91,	115,	0},	
            {117,	106,	93,	104,	118,	94,	92,	116,	0},	
            {118,	107,	94,	105,	119,	95,	93,	117,	0},	
            {119,	182,	95,	106,	178,	94,	118,	0,	0},	
            {120,	109,	96,	181,	121,	97,	185,	0,	0},	
            {121,	110,	97,	108,	122,	98,	96,	120,	0},	
            {122,	111,	98,	109,	123,	99,	97,	121,	0},	
            {123,	112,	99,	110,	124,	100,	98,	122,	0},	
            {124,	113,	100,	111,	125,	101,	99,	123,	0},	
            {125,	114,	101,	112,	126,	102,	100,	124,	0},	
            {126,	115,	102,	113,	127,	103,	101,	125,	0},	
            {127,	116,	103,	114,	128,	104,	102,	126,	0},	
            {128,	117,	104,	115,	129,	105,	103,	127,	0},	
            {129,	118,	105,	116,	130,	106,	104,	128,	0},	
            {130,	119,	106,	117,	131,	107,	105,	129,	0},	
            {131,	182,	107,	118,	186,	106,	130,	0,	0},	
            {132,	121,	108,	185,	133,	109,	181,	0,	0},	
            {133,	122,	109,	120,	134,	110,	108,	132,	0},	
            {134,	123,	110,	121,	135,	111,	109,	133,	0},	
            {135,	124,	111,	122,	136,	112,	110,	134,	0},	
            {136,	125,	112,	123,	137,	113,	111,	135,	0},	
            {137,	126,	113,	124,	138,	114,	112,	136,	0},	
            {138,	127,	114,	125,	139,	115,	113,	137,	0},	
            {139,	128,	115,	126,	140,	116,	114,	138,	0},	
            {140,	129,	116,	127,	141,	117,	115,	139,	0},	
            {141,	130,	117,	128,	142,	118,	116,	140,	0},	
            {142,	131,	118,	129,	143,	119,	117,	141,	0},	
            {143,	186,	119,	130,	182,	118,	142,	0,	0},	
            {190,	133,	120,	185,	121,	189,	0,	0,	0},	
            {190,	134,	121,	132,	191,	122,	120,	0,	0},	
            {191,	135,	122,	133,	123,	121,	190,	0,	0},	
            {191,	136,	123,	134,	124,	122,	192,	0,	0},	
            {192,	137,	124,	135,	125,	123,	191,	0,	0},	
            {192,	138,	125,	136,	126,	124,	193,	0,	0},	
            {193,	139,	126,	137,	127,	125,	192,	0,	0},	
            {193,	140,	127,	138,	128,	194,	126,	0,	0},	
            {194,	141,	128,	139,	129,	127,	193,	0,	0},	
            {194,	142,	129,	140,	130,	128,	195,	0,	0},	
            {195,	143,	130,	141,	194,	131,	129,	0,	0},	
            {195,	186,	131,	142,	196,	130,	0,	0,	0},	
            {154,	145,	233,	243,	155,	232,	0,	0,	0},	
            {155,	146,	233,	144,	156,	234,	154,	0,	0},	
            {156,	147,	234,	145,	157,	233,	155,	0,	0},	
            {157,	148,	234,	146,	158,	235,	156,	0,	0},	
            {158,	149,	235,	147,	159,	234,	157,	0,	0},	
            {159,	150,	235,	148,	160,	236,	158,	0,	0},	
            {160,	151,	236,	149,	161,	235,	159,	0,	0},	
            {161,	152,	236,	150,	162,	237,	160,	0,	0},	
            {162,	153,	237,	151,	163,	236,	161,	0,	0},	
            {163,	244,	237,	152,	238,	162,	0,	0,	0},	
            {164,	155,	144,	243,	165,	145,	249,	0,	0},	
            {165,	156,	145,	154,	146,	144,	164,	0,	0},	
            {1,	157,	146,	155,	2,	147,	145,	165,	0},	
            {2,	3,	158,	147,	156,	4,	148,	146,	0},	
            {4,	5,	159,	148,	157,	149,	147,	3,	6},	
            {6,	7,	160,	149,	158,	150,	148,	5,	8},	
            {8,	9,	161,	150,	159,	151,	149,	7,	10},	
            {10,	11,	162,	151,	160,	166,	152,	150,	9},	
            {166,	163,	152,	161,	167,	153,	151,	11,	0},	
            {167,	244,	153,	162,	250,	152,	166,	0,	0},	
            {168,	165,	154,	249,	169,	155,	243,	0,	0},	
            {169,	12,	155,	164,	24,	156,	154,	168,	0},	
            {170,	167,	162,	23,	11,	171,	163,	161,	35},	
            {171,	250,	163,	166,	244,	162,	170,	0,	0},	
            {172,	169,	164,	249,	173,	165,	255,	0,	0},	
            {173,	36,	24,	165,	168,	48,	164,	172,	0},	
            {174,	171,	166,	35,	47,	175,	167,	23,	59},	
            {175,	250,	167,	170,	256,	166,	174,	0,	0},	
            {176,	173,	168,	255,	177,	169,	249,	0,	0},	
            {177,	60,	48,	169,	172,	72,	36,	168,	176},	
            {178,	175,	170,	59,	71,	179,	171,	47,	83},	
            {179,	256,	171,	174,	250,	170,	178,	0,	0},	
            {180,	177,	172,	255,	181,	173,	261,	0,	0},	
            {181,	84,	72,	173,	176,	96,	60,	172,	180},	
            {182,	179,	174,	83,	95,	183,	175,	71,	107},	
            {183,	256,	175,	178,	262,	174,	182,	0,	0},	
            {184,	181,	176,	261,	185,	177,	255,	0,	0},	
            {185,	108,	96,	177,	180,	120,	176,	184,	0},	
            {186,	183,	178,	107,	119,	187,	179,	95,	131},	
            {187,	262,	179,	182,	256,	178,	186,	0,	0},	
            {188,	185,	180,	261,	189,	181,	267,	0,	0},	
            {189,	132,	120,	181,	184,	190,	180,	188,	0},	
            {196,	187,	182,	131,	143,	197,	183,	119,	195},	
            {197,	262,	183,	186,	268,	182,	196,	0,	0},	
            {198,	189,	184,	267,	199,	185,	261,	0,	0},	
            {199,	190,	185,	188,	200,	132,	184,	198,	0},	
            {200,	191,	133,	132,	189,	201,	134,	185,	199},	
            {201,	192,	135,	134,	190,	202,	136,	133,	200},	
            {202,	193,	137,	136,	191,	203,	138,	135,	201},	
            {203,	194,	139,	138,	192,	204,	140,	137,	202},	
            {204,	195,	141,	140,	193,	205,	142,	139,	203},	
            {205,	196,	143,	142,	194,	206,	186,	141,	204},	
            {206,	197,	186,	195,	207,	187,	143,	205,	0},	
            {207,	268,	187,	196,	262,	186.206,	0,	0},	
            {199,	188,	267,	189,	0,	0,	0,	0,	0},	
            {200,	189,	198,	190,	188,	0,	0,	0,	0},	
            {201,	190,	199,	191,	189,	0,	0,	0,	0},	
            {202,	191,	200,	192,	190,	0,	0,	0,	0},	
            {203,	192,	201,	193,	191,	0,	0,	0,	0},	
            {204,	193,	202,	194,	192,	0,	0,	0,	0},	
            {205,	194,	203,	195,	193,	0,	0,	0,	0},	
            {206,	195,	204,	196,	194,	0,	0,	0,	0},	
            {207,	196,	205,	197,	195,	0,	0,	0,	0},	
            {268,	197,	206,	196,	0,	0,	0,	0,	0},	
            {0,	0,	0,	0,	0,	0,	0,	0,	0},	
            {0,	0,	0,	0,	0,	0,	0,	0,	0},	
            {221,	211,	222,	0,	0,	0,	0,	0,	0},	
            {222,	212,	210,	223,	221,	0,	0,	0,	0},	
            {223,	213,	211,	224,	222,	0,	0,	0,	0},	
            {224,	214,	212,	225,	223,	0,	0,	0,	0},	
            {225,	215,	213,	226,	224,	0,	0,	0,	0},	
            {226,	216,	214,	227,	225,	0,	0,	0,	0},	
            {227,	215,	228,	226,	0,	0,	0,	0,	0},	
            {0,	0,	0,	0,	0,	0,	0,	0,	0},	
            {0,	0,	0,	0,	0,	0,	0,	0,	0},	
            {0,	0,	0,	0,	0,	0,	0,	0,	0},	
            {231,	221,	232,	230,	0,	0,	0,	0,	0},	
            {232,	222,	210,	220,	233,	211,	231,	0,	0},	
            {233,	223,	211,	221,	234,	212,	210,	232,	0},	
            {234,	224,	212,	222,	235,	213,	211,	233,	0},	
            {235,	225,	213,	223,	236,	214,	212,	234,	0},	
            {236,	226,	214,	224,	237,	215,	213,	235,	0},	
            {237,	227,	215,	225,	238,	216,	214,	236,	0},	
            {238,	228,	216,	226,	239,	215,	237,	0,	0},	
            {239,	227,	240,	216,	238,	0,	0,	0,	0},	
            {0,	0,	0,	0,	0,	0,	0,	0,	0},	
            {241,	231,	242,	220,	0,	0,	0,	0,	0},	
            {242,	232,	220,	230,	243,	221,	241,	0,	0},	
            {243,	233,	221,	231,	144,	222,	220,	242,	0},	
            {144,	145,	234,	222,	232,	146,	223,	221,	243},	
            {146,	147,	235,	223,	233,	148,	224,	222,	145},	
            {148,	149,	236,	224,	234,	150,	225,	223,	147},	
            {150,	151,	237,	225,	235,	152,	226,	224,	149},	
            {152,	153,	238,	226,	236,	244,	227,	225,	151},	
            {244,	239,	227,	237,	245,	228,	226,	153,	0},	
            {245,	240,	228,	238,	246,	227,	244,	0,	0},	
            {246,	239,	228,	245,	0,	0,	0,	0,	0},	
            {247,	242,	230,	248,	231,	0,	0,	0,	0},	
            {248,	243,	231,	241,	249,	232,	230,	247,	0},	
            {249,	154,	144,	232,	242,	164,	233,	231,	248},	
            {250,	245,	238,	152,	163,	251,	239,	237,	167},	
            {251,	246,	239,	244,	252,	240,	238,	250,	0},	
            {252,	240,	245,	239,	251,	0,	0,	0,	0},	
            {253,	248,	241,	254,	242,	0,	0,	0,	0},	
            {254,	249,	242,	247,	255,	243,	241,	253,	0},	
            {255,	168,	164,	243,	248,	172,	154,	242,	254},	
            {256,	251,	244,	167,	171,	257,	245,	163,	175},	
            {257,	252,	245,	250,	258,	246,	244,	256,	0},	
            {258,	246,	251,	245,	257,	0,	0,	0,	0},	
            {259,	254,	247,	260,	248,	0,	0,	0,	0},	
            {260,	255,	248,	253,	261,	249,	247,	259,	0},	
            {261,	176,	172,	249,	254,	180,	168,	248,	260},	
            {262,	257,	250,	175,	179,	263,	251,	171,	183},	
            {263,	258,	251,	256,	264,	252,	250,	262,	0},	
            {264,	252,	257,	251,	263,	0,	0,	0,	0},	
            {265,	260,	253,	266,	254,	0,	0,	0,	0},	
            {266,	261,	254,	259,	267,	255,	253,	265,	0},	
            {267,	184,	180,	255,	260,	188,	176,	254,	266},	
            {268,	263,	256,	183,	187,	269,	257,	179,	197},	
            {269,	264,	257,	262,	270,	258,	256,	268,	0},	
            {270,	258,	263,	257,	269,	0,	0,	0,	0},	
            {271,	266,	259,	272,	260,	0,	0,	0,	0},	
            {272,	267,	260,	265,	261,	259,	271,	0,	0},	
            {273,	198,	188,	261,	266,	184,	260,	272,	0},	
            {269,	262,	197,	207,	263,	187,	0,	0,	0},	
            {270,	263,	268,	264,	262,	0,	0,	0,	0},	
            {264,	269,	263,	0,	0,	0,	0,	0,	0},	
            {272,	265,	266,	0,	0,	0,	0,	0,	0},	
            {266,	271,	267,	265,	0,	0,	0,	0,	0}
            };

};

class FWHit {

   FWDetector detector;

   std::vector<FWSingleHit*> hits; // all hits stored in one event
   std::vector<FWSingleHit*>::iterator hitsIt;
   std::vector<FWSingleHit*>::iterator hitsIt2;
   std::vector<FWClusterHit*> clusterhits; // cluster hits made in one event
   std::vector<FWClusterHit*>::iterator clusterhitsIt;
   
   void makeClusters()
   {
       if (clusterhits.size() > 0) clearcluster();
       // loop over all hits (fired pads) from FW
       hitsIt = hits.begin();
       while (hitsIt != hits.end())
       {
          if (*hitsIt->isActive())
          {
             // create new cluster hit and go recursively over all its neighbours
             clusterhits.push_back( new FWClusterHit( *hitsIt ) );
             hitsIt2 = hits.begin();
             while (hitsIt2 != hits.end())
             {
              if (*hitsIt2->isActive() && detector.isNext(*hitsIt->getId(), *hitsIt2->getId() ) )
              {
                 // there must here be a criterion of time hit separation 
                 // 5 ns time difference between hit components
                 if ( abs(*hitsIt->getTime() - *hitsIt2->getTime()) < 5. )
                 {
                    clusterhits.pop_back().addHit( *hitsIt2 );
                 }
              }
              ++hitsIt2;
             }
          } 
        ++hitsIt;
       }
   }

   public:

      FWHit() {}
      ~FWHit() { clear(); }

      void addHit( HWallHit* p ) { hits.push_back( new FWSingleHit( p ) ); }
      void clearcluster() 
      { 
        for (clusterhitsIt= clusterhits.begin(); clusterhitsIt!=clusterhits.end(); ++clusterhitsIt) delete *clusterhitsIt; clusterhits.clear(); 
      }
      void clear() 
      { 
        for (hitsIt= hits.begin(); hitsIt!=hits.end(); ++hitsIt) delete *hitsIt; hits.clear(); 
        clearcluster();
      }
    
      int getMult() { return clusterhits.size(); }
};


class FWSingleHit {

protected:

float fw_time, fw_charge, fw_cell, fw_theta, fw_phi, 
      fw_distance, fw_x_lab, fw_y_lab, fw_z_lab, 
      fw_beta, fw_p, fw_gamma;
bool  kIsUsed;

      FWSingleHit() : fw_time(0.), fw_charge(0.), fw_cell(0.), fw_theta(0.), fw_phi(0.),
                      fw_distance(0.), fw_x_lab(0.), fw_y_lab(0.), fw_z_lab(0.), 
                      fw_beta(0.), fw_p(0.), fw_gamma(0.), kIsUsed(false) {}

public:
   FWSingleHit(HWallHit* ptr) : kIsUsed(false)
   {
      fw_time = ptr->getTime();
      fw_charge = ptr->getCharge();
      fw_cell = ptr->getCell();
      fw_theta = ptr->getTheta();
      fw_phi = ptr->getPhi();
      fw_distance = ptr->getDistance();
      float x_lab, y_lab, z_lab;
      ptr->getXYZLab( x_lab, y_lab, z_lab );
      fw_x_lab = x_lab;
      fw_y_lab = y_lab;
      fw_z_lab = z_lab;
      // momentum calculation
      fw_beta = ((ptr->getDistance()*cos(ptr->getTheta()*TMath::DegToRad()))/(3*ptr->getTime()*1e2));
      fw_gamma = sqrt(1 - (fw_beta*fw_beta));
      fw_p = (fw_beta*0.93827231)/fw_gamma; // we assume proton mass
   }
   ~FWSingleHit() {}

   void setIsUsed( bool k = true ) { kIsUsed = k; }

   bool isActive() { return kIsUsed; }

   float getTime() const { return fw_time; }
   float getCharge() const { return fw_charge; }
   float getCell() const { return fw_cell; }
   float getTheta() const { return fw_theta; }
   float getPhi() const { return fw_phi; }
   float getDistance() const { return fw_distance; }
   float getX() const { return fw_x_lab; }
   float getY() const { return fw_y_lab; }
   float getZ() const { return fw_z_lab; }
   float getBeta() const { return fw_beta; }
   float getGamma() const { return fw_gamma; }
   float getMom() const { return fw_p; }

};

class FWClusterHit 
{
   std::vector<FWSingleHit*> hits;
   std::vector<FWSingleHit*>::iterator hitsIt;
   float maxCharge, minCharge;

   float getChargeSum() 
   {
      float res = 0.;
      for (hitsIt = hits.begin(); hitsIt != hits.end(); ++hitsIt) res += *hitsIt->getCharge();   
      return res;
   }

   public:
      
      FWClusterHit() : maxCharge(130.), minCharge(20.) {}
      FWClusterHit( FWSignleHit* ptr ) : maxCharge(130.), minCharge(20.) { add( ptr ); }
      FWClusterHit& operator+=(FWSingleHit& src)
      {
         hits.push_back( *src );
         src.setIsUsed();
      }
      void addHit(FWSingleHit *ptr)
      {
         hits.push_back( ptr );
         ptr->setIsUsed();
      }

      int getMult() const { return hits.size(); }
      void setMaxCharge(float mc) { maxCharge = mc; }
      void setMinCharge(float mc) { minCharge = mc; }
      float getMaxCharge() const { return maxCharge; }
      float getMinCharge() const { return minCharge; }
      bool isActive()
      {
         for (hitsIt = hits.begin(); hitsIt != hits.end(); ++hitsIt)
         {
             if (*hitsIt->getCharge() > maxCharge || *hitsIt->getCharge() < minCharge)
                return false;
         }
       return true;
      }

   // calculated as mean weight (charge is weight)
   float getSomething( float (FWSingleHit::*fun)() )
   {
      float res = 0.;
      for (hitsIt = hits.begin(); hitsIt != hits.end(); ++hitsIt)
      {
          res += ( (*hitsIt->*fun)() ) * (*hitsIt->getCharge());
      }
      float charge = getChargeSum();
      if ( charge > 0. ) res /= charge; else res = 0.;
      return res;
   }

   float getTheta() 
   { 
      return getSomething( &FWSingleHit::getTheta );
   }
   float getPhi() 
   { 
      return getSomething( &FWSingleHit::getPhi );
   }
   float getDistance() 
   { 
      return getSomething( &FWSingleHit::getDistance );
   }
   float getTime(const char* str = "mean") 
   {
      float res = -1.;
      if ( std::string("max") == str )
      {
         res = 0.;
         for (hitsIt = hits.begin(); hitsIt != hits.end(); ++hitsIt)
         {
             if (*hitsIt->getTime() > res) res = *hitsIt->getTime();
         }
      }
      else if ( std::string("min") == str )
      {
         res = 1000000.;
         for (hitsIt = hits.begin(); hitsIt != hits.end(); ++hitsIt)
         {
             if (*hitsIt->getTime() < res) res = *hitsIt->getTime();
         }
      }
      else // if ( std::string("mean") == str )
      {
         res = getSomething( &FWSingleHit::getTime );
      }
    return res;
   }
   float getX() 
   {
      return getSomething( &FWSingleHit::getX );
   }
   float getY()
   {
      return getSomething( &FWSingleHit::getY );
   }
   float getZ()
   {
      return getSomething( &FWSingleHit::getZ );
   }

   float getCharge() 
   { 
      return (hits.size() > 0) ? getChargeSum() / hits.size() : 0.;
   }

   float getBeta(const char* str = "mean") 
   {
      // max beta means min time !!!
      float time = -1.;
      if (std::string("max") == str)
      {
         time = getTime("min");
      }
      else if (std::string("min") == str)
      {
         time = getTime("max");
      }
      else
      {
         time = getTime();
      }
    return ((getDistance()*cos(getTheta()*TMath::DegToRad()))/(3*time*1e2));
   }

   float getGamma(const char* str = "mean")
   {
      float beta = -1.;
      if (std::string("max") == str)
      {
         beta = getBeta("max");
      }
      else if (std::string("min") == str)
      {
         beta = getBeta("min");
      } 
      else
      {
         beta = getBeta();
      }
    return sqrt(1 - (beta*beta));
   }

   float getMom(const char* str = "mean")
   {
      float beta = -1.;
      float gamma = -1.;
      if (std::string("max") == str)
      {
         beta = getBeta("max");
         gamma = getGamma("max");
      }
      else if (std::string("min") == str)
      {
         beta = getBeta("min");
         gamma = getGamma("min");
      }
      else
      {
         beta = getBeta();
         gamma = getGamma();
      }
         
    return (beta*0.93827231)/gamma; // we assume proton mass
   }

};


int main()
{



}




