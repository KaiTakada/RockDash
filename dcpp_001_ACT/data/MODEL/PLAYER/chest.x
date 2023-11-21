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
 6.06582;-0.03862;-2.88094;,
 -0.00002;-0.03862;-4.07427;,
 -0.00002;5.64029;-7.15575;,
 8.72297;5.64029;-5.32329;,
 -6.06585;-0.03862;-2.88094;,
 -8.72301;5.64029;-5.32329;,
 -7.79812;-0.03862;0.00000;,
 -10.38489;5.64029;0.00000;,
 -6.06585;-0.03862;2.88094;,
 -8.72301;5.64029;5.32329;,
 -0.00002;-0.03862;4.07427;,
 -0.00002;5.64029;7.15575;,
 6.06582;-0.03862;2.88094;,
 8.72297;5.64029;5.32329;,
 7.79809;-0.03862;0.00000;,
 10.38485;5.64029;0.00000;,
 -0.00002;11.02848;-8.71775;,
 8.97554;11.02848;-6.95521;,
 -8.97558;11.02848;-6.95521;,
 -11.95786;11.02848;0.00000;,
 -8.97558;11.02848;6.95521;,
 -0.00002;11.02848;8.71775;,
 8.97554;11.02848;6.95521;,
 11.95783;11.02848;0.00000;,
 -0.00002;15.50417;-8.85393;,
 9.80741;15.50417;-7.52827;,
 -9.80744;15.50417;-7.52827;,
 -13.13430;15.50417;0.00000;,
 -9.80744;15.50417;7.52827;,
 -0.00002;15.50417;8.85393;,
 9.80741;15.50417;7.52827;,
 13.13426;15.50417;0.00000;,
 -0.00002;20.32048;-8.04351;,
 8.97554;20.32048;-6.95521;,
 -8.97558;20.32048;-6.95521;,
 -11.95786;20.32048;0.00000;,
 -8.97558;20.32048;6.95521;,
 -0.00002;20.32048;8.04351;,
 8.97554;20.32048;6.95521;,
 11.95783;20.32048;0.00000;,
 -0.00002;22.99506;-6.69228;,
 8.14553;22.99506;-5.32329;,
 -8.14556;22.99506;-5.32329;,
 -9.80744;22.99506;0.00000;,
 -8.14556;22.99506;5.32329;,
 -0.00002;22.99506;6.69228;,
 8.14553;22.99506;5.32329;,
 9.80741;22.99506;0.00000;,
 -0.00002;25.17500;-4.07427;,
 4.18206;25.17500;-2.88094;,
 -4.18209;25.17500;-2.88094;,
 -5.91437;25.17500;0.00000;,
 -4.18209;25.17500;2.88094;,
 -0.00002;25.17500;4.07427;,
 4.18206;25.17500;2.88094;,
 5.91433;25.17500;0.00000;,
 -0.00002;-4.57071;0.00000;,
 -0.00002;26.35023;0.00000;;
 
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
  59;
  0.437912;-0.658419;-0.612142;,
  -0.000000;-0.574715;-0.818354;,
  -0.437912;-0.658419;-0.612142;,
  -0.705460;-0.708750;0.000000;,
  -0.437912;-0.658419;0.612142;,
  -0.000000;-0.574715;0.818354;,
  0.437912;-0.658419;0.612142;,
  0.705460;-0.708750;-0.000000;,
  0.587016;-0.401430;-0.703040;,
  -0.000000;-0.382273;-0.924049;,
  -0.587016;-0.401430;-0.703040;,
  -0.929796;-0.368075;0.000000;,
  -0.587016;-0.401430;0.703040;,
  -0.000000;-0.382273;0.924049;,
  0.587016;-0.401430;0.703040;,
  0.929796;-0.368074;-0.000000;,
  0.615178;-0.231265;-0.753706;,
  -0.000000;-0.190624;-0.981663;,
  -0.615178;-0.231265;-0.753706;,
  -0.971692;-0.236252;0.000000;,
  -0.615178;-0.231265;0.753706;,
  -0.000000;-0.190624;0.981663;,
  0.615178;-0.231265;0.753706;,
  0.971692;-0.236253;-0.000000;,
  0.604021;0.013627;-0.796852;,
  -0.000000;0.031607;-0.999500;,
  -0.604021;0.013627;-0.796851;,
  -0.999964;-0.008480;0.000000;,
  -0.604021;0.013627;0.796852;,
  -0.000000;0.031607;0.999500;,
  0.604021;0.013627;0.796852;,
  0.999964;-0.008480;-0.000000;,
  0.557266;0.401721;-0.726688;,
  -0.000000;0.331385;-0.943496;,
  -0.557265;0.401721;-0.726688;,
  -0.913777;0.406217;0.000000;,
  -0.557266;0.401722;0.726688;,
  -0.000000;0.331385;0.943496;,
  0.557266;0.401721;0.726688;,
  0.913777;0.406216;0.000000;,
  0.405215;0.742977;-0.532715;,
  -0.000000;0.659081;-0.752072;,
  -0.405215;0.742977;-0.532715;,
  -0.648040;0.761606;0.000000;,
  -0.405215;0.742977;0.532715;,
  -0.000000;0.659081;0.752072;,
  0.405215;0.742977;0.532715;,
  0.648040;0.761606;0.000000;,
  0.214934;0.928225;-0.303647;,
  -0.000000;0.893298;-0.449464;,
  -0.214934;0.928225;-0.303647;,
  -0.315174;0.949034;0.000000;,
  -0.214934;0.928225;0.303647;,
  -0.000000;0.893298;0.449464;,
  0.214934;0.928225;0.303647;,
  0.315174;0.949034;0.000000;,
  -0.113954;-0.901656;-0.417171;,
  -0.000000;1.000000;0.000000;,
  0.170515;-0.762401;0.624235;;
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
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,16,24,31;,
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
  3;3,2,56;,
  3;4,3,56;,
  3;5,4,58;,
  3;6,5,58;,
  3;7,6,58;,
  3;0,7,56;,
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
  0.361750;0.352525;,
  0.287366;0.352525;,
  0.287366;0.303483;,
  0.394334;0.303483;,
  0.212982;0.352525;,
  0.180398;0.303483;,
  0.191740;0.352525;,
  0.160019;0.303483;,
  0.212982;0.352525;,
  0.180398;0.303483;,
  0.287366;0.352525;,
  0.287366;0.303483;,
  0.361750;0.352525;,
  0.394334;0.303483;,
  0.382992;0.352525;,
  0.414713;0.303483;,
  0.287366;0.256951;,
  0.397431;0.256951;,
  0.177301;0.256951;,
  0.140731;0.256951;,
  0.177301;0.256951;,
  0.287366;0.256951;,
  0.397431;0.256951;,
  0.434002;0.256951;,
  0.287366;0.218299;,
  0.407632;0.218299;,
  0.167100;0.218299;,
  0.126304;0.218299;,
  0.167100;0.218299;,
  0.287366;0.218299;,
  0.407632;0.218299;,
  0.448428;0.218299;,
  0.287366;0.176706;,
  0.397431;0.176706;,
  0.177301;0.176706;,
  0.140731;0.176706;,
  0.177301;0.176706;,
  0.287366;0.176706;,
  0.397431;0.176706;,
  0.434002;0.176706;,
  0.287366;0.153608;,
  0.387253;0.153608;,
  0.187480;0.153608;,
  0.167100;0.153608;,
  0.187480;0.153608;,
  0.287366;0.153608;,
  0.387253;0.153608;,
  0.407632;0.153608;,
  0.287366;0.134783;,
  0.338650;0.134783;,
  0.236083;0.134783;,
  0.214840;0.134783;,
  0.236083;0.134783;,
  0.287366;0.134783;,
  0.338650;0.134783;,
  0.359892;0.134783;,
  0.287366;0.391664;,
  0.287366;0.124633;;
 }
}