
//         Copyright Jasper van Poelgeest 2018.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt)

#include "dmx_ws2812b.hpp"
#include <array>

dwarfNebula::DMX_WS2812B::DMX_WS2812B(uint16_t channel, uint16_t numLeds, uint16_t channel_Modes[16], uint8_t maxChannelMode):
	numLeds(numLeds),
	channel(channel),
	channelMode(0),
	menu('c'),
	settings(0),
	strip(numLeds),
	Dmx(),
	screen(channel, channel_Modes[channelMode]),
	maxChannelMode(maxChannelMode)
{
	for (unsigned int i = 0; i < maxChannelMode; i ++){
		channelModes[i] = channel_Modes[i];
	}
	screen.changeMenu(menu);
}

void dwarfNebula::DMX_WS2812B::start(){
	//DMX::enable_dmx(); //DMX isn't working so this is unnecessary
	while(1){
		if (rotary.buttonPushed()){
			screen.changeMenu(menu);
			settings = 1;
			while(settings){
				screen.changeMenu(menu);
				
				//code to go through the menu
				char encoderState = rotary.getState();
				if (encoderState == 'l' || encoderState == 'r'){
					if (menu == 'c'){
						menu = 'm';
					}
					else if (menu == 'm'){
						menu = 'c';
					}
				}
				
				//code to change the channel
				if (rotary.buttonPushed() && menu == 'c'){
					screen.changeMenu('d');
					while(settings){
						char encoderState = rotary.getState();
						if (encoderState == 'r'){
							if (channel < 508){
								channel++;
								screen.changeChannel(channel);
								hwlib::wait_ms(10); //small wait to update the screen
							}
						}
						else if (encoderState == 'l'){
							if (channel > 1){
								channel--;
								screen.changeChannel(channel);
								hwlib::wait_ms(10); //small wait to update the screen
							}
						}
						if (rotary.buttonPushed()){
							settings = 0;
							screen.changeMenu('c');
						}
					}
				}
				
				//code to change the channelmodes
				if (rotary.buttonPushed() && menu == 'm'){
					screen.changeMenu('n');
					while(settings){
						char encoderState = rotary.getState();
						if (encoderState == 'r' && channelMode < maxChannelMode-1){
							channelMode++;
							screen.changeChannelMode(channelModes[channelMode]);
							hwlib::wait_ms(10); //small wait to update the screen
						}
						else if (encoderState == 'l' && channelMode > 0){
							channelMode--;
							screen.changeChannelMode(channelModes[channelMode]);
							hwlib::wait_ms(10); //small wait to update the screen
						}
						if (rotary.buttonPushed()){
							settings = 0;
							screen.changeMenu('m');
						}
					}
				}
			}
		}
		
		//std::array<int, 512> dmx_data; //dmx isn't working so, I use a predefined array.
		//Dmx.get_data(dmx_data);
		get_data(); // fills the dmx_data-array with predefined numbers.
		
		int ledsPerChannel = numLeds / channelModes[channelMode];
		
		for (unsigned int i = 0; i < channelModes[channelMode]; i ++){ 
			for (unsigned int l = i * ledsPerChannel; l < ledsPerChannel + (i * ledsPerChannel); l++){
				uint8_t r = dmx_data[channel-1+i*4] * (dmx_data[channel+2+i*4]*100 / 255) / 100;
				uint8_t g = dmx_data[channel  +i*4] * (dmx_data[channel+2+i*4]*100 / 255) / 100;
				uint8_t b = dmx_data[channel+1+i*4] * (dmx_data[channel+2+i*4]*100 / 255) / 100;
				strip.setPixelColor(l, Color(r, g, b));
			}
		}
		strip.show();
	}
}

//pre-defined array with "dmx data"
void dwarfNebula::DMX_WS2812B::get_data(){
	dmx_data[0] = 41;
	dmx_data[1] = 35;
	dmx_data[2] = 190;
	dmx_data[3] = 132;
	dmx_data[4] = 225;
	dmx_data[5] = 108;
	dmx_data[6] = 214;
	dmx_data[7] = 174;
	dmx_data[8] = 82;
	dmx_data[9] = 144;
	dmx_data[10] = 73;
	dmx_data[11] = 241;
	dmx_data[12] = 241;
	dmx_data[13] = 187;
	dmx_data[14] = 233;
	dmx_data[15] = 235;
	dmx_data[16] = 179;
	dmx_data[17] = 166;
	dmx_data[18] = 219;
	dmx_data[19] = 60;
	dmx_data[20] = 135;
	dmx_data[21] = 12;
	dmx_data[22] = 62;
	dmx_data[23] = 153;
	dmx_data[24] = 36;
	dmx_data[25] = 94;
	dmx_data[26] = 13;
	dmx_data[27] = 28;
	dmx_data[28] = 6;
	dmx_data[29] = 183;
	dmx_data[30] = 71;
	dmx_data[31] = 222;
	dmx_data[32] = 179;
	dmx_data[33] = 18;
	dmx_data[34] = 77;
	dmx_data[35] = 200;
	dmx_data[36] = 67;
	dmx_data[37] = 187;
	dmx_data[38] = 139;
	dmx_data[39] = 166;
	dmx_data[40] = 31;
	dmx_data[41] = 20;
	dmx_data[42] = 90;
	dmx_data[43] = 125;
	dmx_data[44] = 9;
	dmx_data[45] = 56;
	dmx_data[46] = 37;
	dmx_data[47] = 31;
	dmx_data[48] = 93;
	dmx_data[49] = 212;
	dmx_data[50] = 203;
	dmx_data[51] = 252;
	dmx_data[52] = 150;
	dmx_data[53] = 245;
	dmx_data[54] = 69;
	dmx_data[55] = 59;
	dmx_data[56] = 19;
	dmx_data[57] = 13;
	dmx_data[58] = 137;
	dmx_data[59] = 10;
	dmx_data[60] = 28;
	dmx_data[61] = 219;
	dmx_data[62] = 174;
	dmx_data[63] = 50;
	dmx_data[64] = 32;
	dmx_data[65] = 154;
	dmx_data[66] = 80;
	dmx_data[67] = 238;
	dmx_data[68] = 64;
	dmx_data[69] = 120;
	dmx_data[70] = 54;
	dmx_data[71] = 253;
	dmx_data[72] = 18;
	dmx_data[73] = 73;
	dmx_data[74] = 50;
	dmx_data[75] = 246;
	dmx_data[76] = 158;
	dmx_data[77] = 125;
	dmx_data[78] = 73;
	dmx_data[79] = 220;
	dmx_data[80] = 173;
	dmx_data[81] = 79;
	dmx_data[82] = 20;
	dmx_data[83] = 242;
	dmx_data[84] = 68;
	dmx_data[85] = 64;
	dmx_data[86] = 102;
	dmx_data[87] = 208;
	dmx_data[88] = 107;
	dmx_data[89] = 196;
	dmx_data[90] = 48;
	dmx_data[91] = 183;
	dmx_data[92] = 50;
	dmx_data[93] = 59;
	dmx_data[94] = 161;
	dmx_data[95] = 34;
	dmx_data[96] = 246;
	dmx_data[97] = 34;
	dmx_data[98] = 145;
	dmx_data[99] = 157;
	dmx_data[100] = 225;
	dmx_data[101] = 139;
	dmx_data[102] = 31;
	dmx_data[103] = 218;
	dmx_data[104] = 176;
	dmx_data[105] = 202;
	dmx_data[106] = 153;
	dmx_data[107] = 2;
	dmx_data[108] = 185;
	dmx_data[109] = 114;
	dmx_data[110] = 157;
	dmx_data[111] = 73;
	dmx_data[112] = 44;
	dmx_data[113] = 128;
	dmx_data[114] = 126;
	dmx_data[115] = 197;
	dmx_data[116] = 153;
	dmx_data[117] = 213;
	dmx_data[118] = 233;
	dmx_data[119] = 128;
	dmx_data[120] = 178;
	dmx_data[121] = 234;
	dmx_data[122] = 201;
	dmx_data[123] = 204;
	dmx_data[124] = 83;
	dmx_data[125] = 191;
	dmx_data[126] = 103;
	dmx_data[127] = 214;
	dmx_data[128] = 191;
	dmx_data[129] = 20;
	dmx_data[130] = 214;
	dmx_data[131] = 126;
	dmx_data[132] = 45;
	dmx_data[133] = 220;
	dmx_data[134] = 142;
	dmx_data[135] = 102;
	dmx_data[136] = 131;
	dmx_data[137] = 239;
	dmx_data[138] = 87;
	dmx_data[139] = 73;
	dmx_data[140] = 97;
	dmx_data[141] = 255;
	dmx_data[142] = 105;
	dmx_data[143] = 143;
	dmx_data[144] = 97;
	dmx_data[145] = 205;
	dmx_data[146] = 209;
	dmx_data[147] = 30;
	dmx_data[148] = 157;
	dmx_data[149] = 156;
	dmx_data[150] = 22;
	dmx_data[151] = 114;
	dmx_data[152] = 114;
	dmx_data[153] = 230;
	dmx_data[154] = 29;
	dmx_data[155] = 240;
	dmx_data[156] = 132;
	dmx_data[157] = 79;
	dmx_data[158] = 74;
	dmx_data[159] = 119;
	dmx_data[160] = 2;
	dmx_data[161] = 215;
	dmx_data[162] = 232;
	dmx_data[163] = 57;
	dmx_data[164] = 44;
	dmx_data[165] = 83;
	dmx_data[166] = 203;
	dmx_data[167] = 201;
	dmx_data[168] = 18;
	dmx_data[169] = 30;
	dmx_data[170] = 51;
	dmx_data[171] = 116;
	dmx_data[172] = 158;
	dmx_data[173] = 12;
	dmx_data[174] = 244;
	dmx_data[175] = 213;
	dmx_data[176] = 212;
	dmx_data[177] = 159;
	dmx_data[178] = 212;
	dmx_data[179] = 164;
	dmx_data[180] = 89;
	dmx_data[181] = 126;
	dmx_data[182] = 53;
	dmx_data[183] = 207;
	dmx_data[184] = 50;
	dmx_data[185] = 34;
	dmx_data[186] = 244;
	dmx_data[187] = 204;
	dmx_data[188] = 207;
	dmx_data[189] = 211;
	dmx_data[190] = 144;
	dmx_data[191] = 45;
	dmx_data[192] = 72;
	dmx_data[193] = 211;
	dmx_data[194] = 143;
	dmx_data[195] = 117;
	dmx_data[196] = 230;
	dmx_data[197] = 217;
	dmx_data[198] = 29;
	dmx_data[199] = 42;
	dmx_data[200] = 229;
	dmx_data[201] = 192;
	dmx_data[202] = 247;
	dmx_data[203] = 43;
	dmx_data[204] = 120;
	dmx_data[205] = 129;
	dmx_data[206] = 135;
	dmx_data[207] = 68;
	dmx_data[208] = 14;
	dmx_data[209] = 95;
	dmx_data[210] = 80;
	dmx_data[211] = 0;
	dmx_data[212] = 212;
	dmx_data[213] = 97;
	dmx_data[214] = 141;
	dmx_data[215] = 190;
	dmx_data[216] = 123;
	dmx_data[217] = 5;
	dmx_data[218] = 21;
	dmx_data[219] = 7;
	dmx_data[220] = 59;
	dmx_data[221] = 51;
	dmx_data[222] = 130;
	dmx_data[223] = 31;
	dmx_data[224] = 24;
	dmx_data[225] = 112;
	dmx_data[226] = 146;
	dmx_data[227] = 218;
	dmx_data[228] = 100;
	dmx_data[229] = 84;
	dmx_data[230] = 206;
	dmx_data[231] = 177;
	dmx_data[232] = 133;
	dmx_data[233] = 62;
	dmx_data[234] = 105;
	dmx_data[235] = 21;
	dmx_data[236] = 248;
	dmx_data[237] = 70;
	dmx_data[238] = 106;
	dmx_data[239] = 4;
	dmx_data[240] = 150;
	dmx_data[241] = 115;
	dmx_data[242] = 14;
	dmx_data[243] = 217;
	dmx_data[244] = 22;
	dmx_data[245] = 47;
	dmx_data[246] = 103;
	dmx_data[247] = 104;
	dmx_data[248] = 212;
	dmx_data[249] = 247;
	dmx_data[250] = 74;
	dmx_data[251] = 74;
	dmx_data[252] = 208;
	dmx_data[253] = 87;
	dmx_data[254] = 104;
	dmx_data[255] = 118;
	dmx_data[256] = 250;
	dmx_data[257] = 22;
	dmx_data[258] = 187;
	dmx_data[259] = 17;
	dmx_data[260] = 173;
	dmx_data[261] = 174;
	dmx_data[262] = 36;
	dmx_data[263] = 136;
	dmx_data[264] = 121;
	dmx_data[265] = 254;
	dmx_data[266] = 82;
	dmx_data[267] = 219;
	dmx_data[268] = 37;
	dmx_data[269] = 67;
	dmx_data[270] = 229;
	dmx_data[271] = 60;
	dmx_data[272] = 244;
	dmx_data[273] = 69;
	dmx_data[274] = 211;
	dmx_data[275] = 216;
	dmx_data[276] = 40;
	dmx_data[277] = 206;
	dmx_data[278] = 11;
	dmx_data[279] = 245;
	dmx_data[280] = 197;
	dmx_data[281] = 96;
	dmx_data[282] = 89;
	dmx_data[283] = 61;
	dmx_data[284] = 151;
	dmx_data[285] = 39;
	dmx_data[286] = 138;
	dmx_data[287] = 89;
	dmx_data[288] = 118;
	dmx_data[289] = 45;
	dmx_data[290] = 208;
	dmx_data[291] = 194;
	dmx_data[292] = 201;
	dmx_data[293] = 205;
	dmx_data[294] = 104;
	dmx_data[295] = 212;
	dmx_data[296] = 73;
	dmx_data[297] = 106;
	dmx_data[298] = 121;
	dmx_data[299] = 37;
	dmx_data[300] = 8;
	dmx_data[301] = 97;
	dmx_data[302] = 64;
	dmx_data[303] = 20;
	dmx_data[304] = 177;
	dmx_data[305] = 59;
	dmx_data[306] = 106;
	dmx_data[307] = 165;
	dmx_data[308] = 17;
	dmx_data[309] = 40;
	dmx_data[310] = 193;
	dmx_data[311] = 140;
	dmx_data[312] = 214;
	dmx_data[313] = 169;
	dmx_data[314] = 11;
	dmx_data[315] = 135;
	dmx_data[316] = 151;
	dmx_data[317] = 140;
	dmx_data[318] = 47;
	dmx_data[319] = 241;
	dmx_data[320] = 21;
	dmx_data[321] = 29;
	dmx_data[322] = 154;
	dmx_data[323] = 149;
	dmx_data[324] = 193;
	dmx_data[325] = 155;
	dmx_data[326] = 225;
	dmx_data[327] = 192;
	dmx_data[328] = 126;
	dmx_data[329] = 233;
	dmx_data[330] = 168;
	dmx_data[331] = 154;
	dmx_data[332] = 167;
	dmx_data[333] = 134;
	dmx_data[334] = 194;
	dmx_data[335] = 181;
	dmx_data[336] = 84;
	dmx_data[337] = 191;
	dmx_data[338] = 154;
	dmx_data[339] = 231;
	dmx_data[340] = 217;
	dmx_data[341] = 35;
	dmx_data[342] = 209;
	dmx_data[343] = 85;
	dmx_data[344] = 144;
	dmx_data[345] = 56;
	dmx_data[346] = 40;
	dmx_data[347] = 209;
	dmx_data[348] = 217;
	dmx_data[349] = 108;
	dmx_data[350] = 161;
	dmx_data[351] = 102;
	dmx_data[352] = 94;
	dmx_data[353] = 78;
	dmx_data[354] = 225;
	dmx_data[355] = 48;
	dmx_data[356] = 156;
	dmx_data[357] = 254;
	dmx_data[358] = 217;
	dmx_data[359] = 113;
	dmx_data[360] = 159;
	dmx_data[361] = 226;
	dmx_data[362] = 165;
	dmx_data[363] = 226;
	dmx_data[364] = 12;
	dmx_data[365] = 155;
	dmx_data[366] = 180;
	dmx_data[367] = 71;
	dmx_data[368] = 101;
	dmx_data[369] = 56;
	dmx_data[370] = 42;
	dmx_data[371] = 70;
	dmx_data[372] = 137;
	dmx_data[373] = 169;
	dmx_data[374] = 130;
	dmx_data[375] = 121;
	dmx_data[376] = 122;
	dmx_data[377] = 118;
	dmx_data[378] = 120;
	dmx_data[379] = 194;
	dmx_data[380] = 99;
	dmx_data[381] = 177;
	dmx_data[382] = 38;
	dmx_data[383] = 223;
	dmx_data[384] = 218;
	dmx_data[385] = 41;
	dmx_data[386] = 109;
	dmx_data[387] = 62;
	dmx_data[388] = 98;
	dmx_data[389] = 224;
	dmx_data[390] = 150;
	dmx_data[391] = 18;
	dmx_data[392] = 52;
	dmx_data[393] = 191;
	dmx_data[394] = 57;
	dmx_data[395] = 166;
	dmx_data[396] = 63;
	dmx_data[397] = 137;
	dmx_data[398] = 94;
	dmx_data[399] = 241;
	dmx_data[400] = 109;
	dmx_data[401] = 14;
	dmx_data[402] = 227;
	dmx_data[403] = 108;
	dmx_data[404] = 40;
	dmx_data[405] = 161;
	dmx_data[406] = 30;
	dmx_data[407] = 32;
	dmx_data[408] = 29;
	dmx_data[409] = 203;
	dmx_data[410] = 194;
	dmx_data[411] = 3;
	dmx_data[412] = 63;
	dmx_data[413] = 65;
	dmx_data[414] = 7;
	dmx_data[415] = 132;
	dmx_data[416] = 15;
	dmx_data[417] = 20;
	dmx_data[418] = 5;
	dmx_data[419] = 101;
	dmx_data[420] = 27;
	dmx_data[421] = 40;
	dmx_data[422] = 97;
	dmx_data[423] = 201;
	dmx_data[424] = 197;
	dmx_data[425] = 231;
	dmx_data[426] = 44;
	dmx_data[427] = 142;
	dmx_data[428] = 70;
	dmx_data[429] = 54;
	dmx_data[430] = 8;
	dmx_data[431] = 220;
	dmx_data[432] = 243;
	dmx_data[433] = 168;
	dmx_data[434] = 141;
	dmx_data[435] = 254;
	dmx_data[436] = 190;
	dmx_data[437] = 242;
	dmx_data[438] = 235;
	dmx_data[439] = 113;
	dmx_data[440] = 255;
	dmx_data[441] = 160;
	dmx_data[442] = 208;
	dmx_data[443] = 59;
	dmx_data[444] = 117;
	dmx_data[445] = 6;
	dmx_data[446] = 140;
	dmx_data[447] = 126;
	dmx_data[448] = 135;
	dmx_data[449] = 120;
	dmx_data[450] = 115;
	dmx_data[451] = 77;
	dmx_data[452] = 208;
	dmx_data[453] = 190;
	dmx_data[454] = 130;
	dmx_data[455] = 190;
	dmx_data[456] = 219;
	dmx_data[457] = 194;
	dmx_data[458] = 70;
	dmx_data[459] = 65;
	dmx_data[460] = 43;
	dmx_data[461] = 140;
	dmx_data[462] = 250;
	dmx_data[463] = 48;
	dmx_data[464] = 127;
	dmx_data[465] = 112;
	dmx_data[466] = 240;
	dmx_data[467] = 167;
	dmx_data[468] = 84;
	dmx_data[469] = 134;
	dmx_data[470] = 50;
	dmx_data[471] = 149;
	dmx_data[472] = 170;
	dmx_data[473] = 91;
	dmx_data[474] = 104;
	dmx_data[475] = 19;
	dmx_data[476] = 11;
	dmx_data[477] = 230;
	dmx_data[478] = 252;
	dmx_data[479] = 245;
	dmx_data[480] = 202;
	dmx_data[481] = 190;
	dmx_data[482] = 125;
	dmx_data[483] = 159;
	dmx_data[484] = 137;
	dmx_data[485] = 138;
	dmx_data[486] = 65;
	dmx_data[487] = 27;
	dmx_data[488] = 253;
	dmx_data[489] = 184;
	dmx_data[490] = 79;
	dmx_data[491] = 104;
	dmx_data[492] = 246;
	dmx_data[493] = 114;
	dmx_data[494] = 123;
	dmx_data[495] = 20;
	dmx_data[496] = 153;
	dmx_data[497] = 205;
	dmx_data[498] = 211;
	dmx_data[499] = 13;
	dmx_data[500] = 240;
	dmx_data[501] = 68;
	dmx_data[502] = 58;
	dmx_data[503] = 180;
	dmx_data[504] = 166;
	dmx_data[505] = 102;
	dmx_data[506] = 83;
	dmx_data[507] = 51;
	dmx_data[508] = 11;
	dmx_data[509] = 203;
	dmx_data[510] = 161;
	dmx_data[511] = 16;
}
