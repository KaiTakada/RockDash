xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 58;
 -1.24746;-28.65139;2.71938;,
 -0.00000;-28.65139;3.14629;,
 -0.00000;-22.93796;3.96206;,
 -1.66298;-22.93796;3.36658;,
 1.24746;-28.65139;2.71938;,
 1.66298;-22.93796;3.36658;,
 1.86297;-28.65139;0.36042;,
 2.49027;-22.93796;0.36042;,
 1.24746;-28.65139;-0.66351;,
 1.66298;-22.93796;-1.05355;,
 0.00000;-28.65139;-1.09042;,
 0.00000;-22.93796;-1.64902;,
 -1.24746;-28.65139;-0.66351;,
 -1.66298;-22.93796;-1.05355;,
 -1.86297;-28.65139;0.36042;,
 -2.49027;-22.93796;0.36042;,
 -0.00000;-15.38248;5.19610;,
 -2.69189;-15.38248;4.16112;,
 2.69189;-15.38248;4.16112;,
 3.41601;-15.38248;0.36042;,
 2.69189;-15.38248;-1.38047;,
 0.00000;-15.38248;-2.24218;,
 -2.69189;-15.38248;-1.38047;,
 -3.41601;-15.38248;0.36042;,
 -0.00000;-7.12042;5.39686;,
 -2.98109;-7.12042;4.40524;,
 2.98109;-7.12042;4.40524;,
 3.53753;-7.12042;0.36042;,
 2.69362;-7.12042;-1.36143;,
 0.00000;-7.12042;-2.35305;,
 -2.69362;-7.12042;-1.36143;,
 -3.53753;-7.12042;0.36042;,
 -0.00000;-1.03386;4.36256;,
 -2.40442;-1.03386;3.21229;,
 2.40442;-1.03386;3.21229;,
 3.12854;-1.03386;0.36042;,
 2.40442;-1.03386;-1.40192;,
 0.00000;-1.03386;-2.30863;,
 -2.40442;-1.03386;-1.40192;,
 -3.12854;-1.03386;0.36042;,
 0.00000;1.67036;3.83397;,
 -1.58084;1.67036;3.23850;,
 1.58084;1.67036;3.23850;,
 2.69362;1.67036;0.36042;,
 1.58084;1.67036;-1.35845;,
 0.00000;1.67036;-2.10613;,
 -1.58084;1.67036;-1.35845;,
 -2.69362;1.67036;0.36042;,
 0.00000;4.95965;3.14629;,
 -0.80643;4.95965;2.71938;,
 0.80643;4.95965;2.71938;,
 1.40866;4.95965;0.36042;,
 0.80643;4.95965;-1.18369;,
 0.00000;4.95965;-1.61059;,
 -0.80643;4.95965;-1.18369;,
 -1.40866;4.95965;0.36042;,
 -0.00000;-34.63534;0.36042;,
 0.00000;6.11470;0.36042;;
 
 64;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,0,3,15;,
 4;3,2,16,17;,
 4;2,5,18,16;,
 4;5,7,19,18;,
 4;7,9,20,19;,
 4;9,11,21,20;,
 4;11,13,22,21;,
 4;13,15,23,22;,
 4;15,3,17,23;,
 4;17,16,24,25;,
 4;16,18,26,24;,
 4;18,19,27,26;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,17,25,31;,
 4;25,24,32,33;,
 4;24,26,34,32;,
 4;26,27,35,34;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,25,33,39;,
 4;33,32,40,41;,
 4;32,34,42,40;,
 4;34,35,43,42;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,33,41,47;,
 4;41,40,48,49;,
 4;40,42,50,48;,
 4;42,43,51,50;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,41,49,55;,
 3;1,0,56;,
 3;4,1,56;,
 3;6,4,56;,
 3;8,6,56;,
 3;10,8,56;,
 3;12,10,56;,
 3;14,12,56;,
 3;0,14,56;,
 3;49,48,57;,
 3;48,50,57;,
 3;50,51,57;,
 3;51,52,57;,
 3;52,53,57;,
 3;53,54,57;,
 3;54,55,57;,
 3;55,49,57;;
 
 MeshMaterialList {
  1;
  64;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\PLAYER\\human_body_use.png";   }
  }
 }
 MeshNormals {
  63;
  -0.711513;-0.262266;0.651894;,
  0.000000;-0.284458;0.958688;,
  0.711513;-0.262266;0.651894;,
  0.969659;-0.202158;-0.137451;,
  0.620380;-0.177771;-0.763889;,
  0.000000;-0.166206;-0.986091;,
  -0.620380;-0.177771;-0.763889;,
  -0.969659;-0.202158;-0.137451;,
  -0.734345;-0.146279;0.662827;,
  0.000000;-0.148733;0.988877;,
  0.734345;-0.146279;0.662827;,
  0.984449;-0.122981;-0.125442;,
  0.641739;-0.104453;-0.759777;,
  0.000000;-0.089006;-0.996031;,
  -0.641739;-0.104453;-0.759777;,
  -0.984449;-0.122981;-0.125442;,
  -0.755988;-0.097854;0.647230;,
  0.000000;-0.095709;0.995409;,
  0.755988;-0.097854;0.647230;,
  0.989339;-0.077278;-0.123439;,
  0.664062;-0.058434;-0.745390;,
  0.000000;-0.044048;-0.999029;,
  -0.664062;-0.058434;-0.745390;,
  -0.989339;-0.077278;-0.123439;,
  -0.632825;0.093320;0.768651;,
  0.000000;0.083663;0.996494;,
  0.632825;0.093320;0.768651;,
  0.991981;0.028964;-0.123024;,
  0.678164;0.012998;-0.734795;,
  0.000000;0.001736;-0.999998;,
  -0.678164;0.012998;-0.734795;,
  -0.991981;0.028964;-0.123024;,
  -0.743610;0.179427;0.644088;,
  0.000000;0.182261;0.983250;,
  0.743610;0.179427;0.644088;,
  0.983729;0.149057;-0.100293;,
  0.676528;0.095833;-0.730155;,
  0.000000;0.055582;-0.998454;,
  -0.676528;0.095833;-0.730155;,
  -0.983729;0.149057;-0.100293;,
  -0.719285;0.237509;0.652854;,
  0.000000;0.193194;0.981161;,
  0.719285;0.237509;0.652854;,
  0.960295;0.266639;-0.082083;,
  0.676408;0.187847;-0.712170;,
  0.000000;0.128922;-0.991655;,
  -0.676408;0.187847;-0.712170;,
  -0.960295;0.266639;-0.082083;,
  -0.610637;0.621362;0.490950;,
  0.000000;0.658408;0.752661;,
  0.610637;0.621362;0.490950;,
  0.819730;0.569368;-0.062154;,
  0.604822;0.555533;-0.570591;,
  0.000000;0.577983;-0.816049;,
  -0.604822;0.555533;-0.570591;,
  -0.819730;0.569368;-0.062154;,
  0.000000;-0.422059;0.906568;,
  -0.000000;0.998239;-0.059328;,
  0.986478;-0.026571;0.161726;,
  -0.986478;-0.026571;0.161726;,
  0.945663;-0.294411;-0.138002;,
  -0.320679;-0.273003;-0.906992;,
  -0.926480;-0.288439;0.241741;;
  64;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,8,16,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,58;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,16,59,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,24,32,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,32,40,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,40,48,55;,
  3;1,0,56;,
  3;2,1,56;,
  3;3,2,60;,
  3;4,3,60;,
  3;5,4,61;,
  3;6,5,61;,
  3;7,6,61;,
  3;0,7,62;,
  3;48,49,57;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,48,57;;
 }
 MeshTextureCoords {
  58;
  0.885860;0.575231;,
  0.871618;0.573919;,
  0.871505;0.530347;,
  0.890562;0.532120;,
  0.857709;0.575433;,
  0.852913;0.532380;,
  0.851557;0.583356;,
  0.844501;0.542154;,
  0.858920;0.586756;,
  0.854444;0.546713;,
  0.873307;0.588097;,
  0.873755;0.548538;,
  0.887347;0.586550;,
  0.892577;0.546446;,
  0.893885;0.583050;,
  0.901371;0.541757;,
  0.871293;0.471892;,
  0.902304;0.474838;,
  0.841091;0.475239;,
  0.833950;0.487017;,
  0.842831;0.492419;,
  0.874297;0.494933;,
  0.905041;0.492005;,
  0.912493;0.486497;,
  0.871516;0.410836;,
  0.906028;0.413484;,
  0.837783;0.413906;,
  0.832570;0.425785;,
  0.842900;0.430850;,
  0.874676;0.433628;,
  0.905615;0.430456;,
  0.914516;0.425273;,
  0.872158;0.368592;,
  0.900389;0.371632;,
  0.844850;0.371960;,
  0.837348;0.380050;,
  0.846371;0.385036;,
  0.874906;0.387478;,
  0.902673;0.384698;,
  0.910223;0.379615;,
  0.872476;0.349780;,
  0.891017;0.351304;,
  0.854414;0.351516;,
  0.842445;0.359550;,
  0.856064;0.364292;,
  0.874932;0.366294;,
  0.893168;0.364074;,
  0.905345;0.359182;,
  0.872882;0.326814;,
  0.882435;0.327906;,
  0.863679;0.328012;,
  0.857535;0.334428;,
  0.865191;0.338611;,
  0.874859;0.339732;,
  0.884166;0.338503;,
  0.890528;0.334241;,
  0.872499;0.625956;,
  0.874080;0.325509;;
 }
}
