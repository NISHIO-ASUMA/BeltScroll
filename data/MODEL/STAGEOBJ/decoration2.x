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
 28;
 29.95942;20.03017;0.00000;,
 29.95941;15.03017;-8.66025;,
 -29.95941;15.03017;-8.66025;,
 -29.95941;20.03017;0.00000;,
 29.75399;5.03017;-8.66025;,
 -29.95941;5.03017;-8.66025;,
 29.95941;0.03017;0.00000;,
 -29.95942;0.03017;0.00000;,
 29.99579;-0.03529;-0.00000;,
 29.54072;4.94635;-8.76160;,
 57.65210;15.44219;-8.76160;,
 60.18137;11.06136;0.00000;,
 29.80640;15.01602;-8.76160;,
 52.59365;24.20380;-8.76160;,
 29.86107;20.32754;0.00000;,
 50.06438;28.58459;0.00000;,
 73.10338;36.89793;-8.76160;,
 77.09273;33.64636;0.00000;,
 64.24603;42.42350;-8.76160;,
 60.37091;46.65258;0.00000;,
 75.67747;66.44716;-8.76160;,
 80.68038;65.69946;0.00000;,
 65.67163;67.94256;-8.76160;,
 60.66862;68.69023;0.00000;,
 74.80389;94.19435;-8.76160;,
 79.76082;93.64880;0.00000;,
 64.88986;94.01471;-8.76160;,
 59.93281;93.00621;0.00000;;
 
 15;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;8,9,10,11;,
 4;9,12,13,10;,
 4;12,14,15,13;,
 4;11,10,16,17;,
 4;10,13,18,16;,
 4;13,15,19,18;,
 4;17,16,20,21;,
 4;16,18,22,20;,
 4;18,19,23,22;,
 4;21,20,24,25;,
 4;20,22,26,24;,
 4;22,23,27,26;;
 
 MeshMaterialList {
  1;
  15;
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
   0.599216;0.467451;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  13;
  0.000000;0.866025;-0.500000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.866025;-0.500000;,
  -0.868907;-0.026174;-0.494282;,
  0.869932;0.028004;-0.492376;,
  -0.327339;0.806376;-0.492551;,
  0.303052;-0.818005;-0.488905;,
  -0.557126;0.653450;-0.512459;,
  0.519973;-0.689453;-0.504265;,
  -0.836461;0.246979;-0.489218;,
  0.812803;-0.310669;-0.492785;,
  -0.878428;0.002489;-0.477868;,
  0.875296;-0.029807;-0.482667;;
  15;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;6,6,8,8;,
  4;1,1,1,1;,
  4;5,5,7,7;,
  4;8,8,10,10;,
  4;1,1,1,1;,
  4;7,7,9,9;,
  4;10,10,12,12;,
  4;1,1,1,1;,
  4;9,9,11,11;,
  4;12,12,4,4;,
  4;1,1,1,1;,
  4;11,11,3,3;;
 }
 MeshTextureCoords {
  28;
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.777780;0.500000;,
  0.777780;0.666670;,
  0.833330;0.666670;,
  0.833330;0.500000;,
  0.777780;0.833330;,
  0.833330;0.833330;,
  0.777780;1.000000;,
  0.833330;1.000000;,
  0.888890;0.666670;,
  0.888890;0.500000;,
  0.888890;0.833330;,
  0.888890;1.000000;,
  0.944440;0.666670;,
  0.944440;0.500000;,
  0.944440;0.833330;,
  0.944440;1.000000;,
  1.000000;0.666670;,
  1.000000;0.500000;,
  1.000000;0.833330;,
  1.000000;1.000000;;
 }
}
