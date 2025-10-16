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
 20;
 -0.05993;16.70182;-7.55694;,
 8.06000;15.83507;-3.84855;,
 6.99289;0.30750;-3.69515;,
 -0.03354;0.32278;-7.47018;,
 8.06000;15.83507;3.56824;,
 7.25566;0.42903;3.46133;,
 -0.05993;16.70182;7.27665;,
 -0.03354;0.42903;6.75829;,
 -8.17986;15.83507;3.56824;,
 -6.81578;0.42903;3.30499;,
 -8.17986;15.83507;-3.84855;,
 -6.81983;0.31091;-3.67521;,
 -0.05993;16.70182;-7.55694;,
 -0.03354;0.32278;-7.47018;,
 -0.05993;19.81096;-0.14014;,
 -0.05993;19.81096;-0.14014;,
 -0.05993;19.81096;-0.14014;,
 -0.05993;19.81096;-0.14014;,
 -0.05993;19.81096;-0.14014;,
 -0.05993;19.81096;-0.14014;;
 
 12;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 3;14,1,0;,
 3;15,4,1;,
 3;16,6,4;,
 3;17,8,6;,
 3;18,10,8;,
 3;19,12,10;;
 
 MeshMaterialList {
  4;
  12;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.006400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.295200;0.357600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  15;
  -0.000000;1.000000;0.000000;,
  -0.004137;-0.028899;-0.999574;,
  0.444243;-0.022685;-0.895619;,
  0.998010;-0.060514;-0.017722;,
  -0.011379;-0.038945;0.999177;,
  -0.432981;-0.042508;0.900400;,
  -0.996144;-0.087724;0.001027;,
  0.412356;-0.028079;0.910590;,
  -0.451641;-0.028990;-0.891729;,
  0.360176;0.913234;-0.190464;,
  0.000000;0.922244;-0.386607;,
  0.360176;0.913234;0.190464;,
  0.000000;0.922244;0.386607;,
  -0.360176;0.913234;0.190464;,
  -0.360176;0.913234;-0.190464;;
  12;
  4;1,2,2,1;,
  4;3,3,3,3;,
  4;7,4,4,7;,
  4;4,5,5,4;,
  4;6,6,6,6;,
  4;8,1,1,8;,
  3;0,9,10;,
  3;0,11,9;,
  3;0,12,11;,
  3;0,13,12;,
  3;0,14,13;,
  3;0,10,14;;
 }
 MeshTextureCoords {
  20;
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;;
 }
}
