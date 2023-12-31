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
 44;
 -10.00000;10.00000;10.00000;,
 10.00000;10.00000;10.00000;,
 10.00000;10.00000;-10.00000;,
 -10.00000;10.00000;-10.00000;,
 -10.00000;-10.00000;-10.00000;,
 10.00000;-10.00000;-10.00000;,
 10.00000;-10.00000;10.00000;,
 -10.00000;-10.00000;10.00000;,
 4.50225;-4.03139;-4.50225;,
 10.00000;-10.00000;-10.00000;,
 -10.00000;-10.00000;-10.00000;,
 -4.50225;-4.03139;-4.50225;,
 -8.44022;-0.01735;-8.44022;,
 8.44022;-0.01711;-8.44022;,
 4.50225;-4.03139;4.50225;,
 10.00000;-10.00000;-10.00000;,
 4.50225;-4.03139;-4.50225;,
 8.44022;-0.01711;-8.44022;,
 8.44022;-0.08364;8.44022;,
 -4.50225;-4.03139;4.50225;,
 -10.00000;-10.00000;10.00000;,
 10.00000;-10.00000;10.00000;,
 4.50225;-4.03139;4.50225;,
 8.44022;-0.08364;8.44022;,
 -8.44022;-0.08388;8.44022;,
 -4.50225;-4.03139;-4.50225;,
 -10.00000;-10.00000;-10.00000;,
 -4.50225;-4.03139;4.50225;,
 -8.44022;-0.08388;8.44022;,
 -8.44022;-0.01735;-8.44022;,
 -5.22891;3.94039;-5.22891;,
 -10.00000;10.00000;-10.00000;,
 10.00000;10.00000;-10.00000;,
 5.22891;3.94039;-5.22891;,
 5.22891;3.94039;-5.22891;,
 10.00000;10.00000;-10.00000;,
 5.22891;3.94039;5.22891;,
 5.22891;3.94039;5.22891;,
 10.00000;10.00000;10.00000;,
 -10.00000;10.00000;10.00000;,
 -5.22891;3.94039;5.22891;,
 -5.22891;3.94039;5.22891;,
 -10.00000;10.00000;-10.00000;,
 -5.22891;3.94039;-5.22891;;
 
 18;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,11,12,13;,
 4;14,6,15,16;,
 4;14,16,17,18;,
 4;19,20,21,22;,
 4;19,22,23,24;,
 4;25,26,7,27;,
 4;25,27,28,29;,
 4;30,31,32,33;,
 4;30,33,13,12;,
 4;34,35,1,36;,
 4;34,36,18,17;,
 4;37,38,39,40;,
 4;37,40,24,23;,
 4;41,0,42,43;,
 4;41,43,29,28;;
 
 MeshMaterialList {
  1;
  18;
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
   0.759216;0.000000;0.787451;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  18;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000005;-0.700297;-0.713851;,
  0.711616;-0.702567;-0.001389;,
  0.000005;-0.706238;0.707975;,
  0.000000;0.677499;-0.735524;,
  0.735524;0.677499;0.000000;,
  0.000000;0.677499;0.735524;,
  0.000000;-0.618620;-0.785690;,
  0.785690;-0.618620;-0.000000;,
  0.000000;-0.618620;0.785690;,
  -0.735524;0.677499;0.000000;,
  -0.711595;-0.702588;-0.001389;,
  -0.000004;0.630092;-0.776521;,
  0.779561;0.626325;0.001239;,
  -0.000004;0.623748;0.781625;,
  -0.785690;-0.618620;0.000000;,
  -0.779579;0.626302;0.001239;;
  18;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;6,6,6,6;,
  4;3,3,3,3;,
  4;7,7,7,7;,
  4;4,4,4,4;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;8,8,8,8;,
  4;13,13,13,13;,
  4;9,9,9,9;,
  4;14,14,14,14;,
  4;10,10,10,10;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;;
 }
 MeshTextureCoords {
  44;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.738410;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.740440;,
  0.000000;0.500610;,
  1.000000;0.500590;,
  1.000000;0.776460;,
  0.000000;1.000000;,
  0.000000;0.738410;,
  0.000000;0.500590;,
  1.000000;0.504530;,
  1.000000;0.778490;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.776460;,
  0.000000;0.504530;,
  1.000000;0.504550;,
  1.000000;0.740440;,
  1.000000;1.000000;,
  0.000000;0.778490;,
  0.000000;0.504550;,
  1.000000;0.500610;,
  0.000000;0.264110;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.266160;,
  0.000000;0.266160;,
  0.000000;0.000000;,
  1.000000;0.225680;,
  0.000000;0.225680;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.223620;,
  0.000000;0.223620;,
  1.000000;0.000000;,
  1.000000;0.264110;;
 }
}
