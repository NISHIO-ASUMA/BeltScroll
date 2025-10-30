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
 -56.10349;75.44464;253.29107;,
 56.22438;77.69680;253.29107;,
 56.22438;138.58780;253.29107;,
 -56.10349;138.58780;253.29107;,
 -56.10349;-80.24689;253.29107;,
 -56.10349;-138.67818;253.29107;,
 56.22438;-138.67818;253.29107;,
 56.22438;-86.29008;253.29107;,
 -56.10349;75.40060;141.69907;,
 -56.10349;75.44464;253.29107;,
 -56.10349;138.58780;253.29107;,
 -56.10349;138.58780;141.61525;,
 -56.10349;-138.67818;141.98259;,
 -56.10349;-138.67818;253.29107;,
 -56.10349;-80.24689;253.29107;,
 -56.10349;-80.12875;141.90502;,
 -56.10349;138.58780;-146.72770;,
 -56.10349;138.58780;-252.96895;,
 -56.10349;75.17579;-252.96895;,
 -56.10349;75.21774;-146.81127;,
 -56.10349;-79.63777;-147.01563;,
 -56.10349;-79.52534;-252.96895;,
 -56.10349;-138.67818;-252.96895;,
 -56.10349;-138.67818;-147.09347;,
 38.58920;-79.63777;-147.01563;,
 38.58920;75.21774;-146.81127;,
 38.58920;-80.12875;141.90502;,
 38.58920;75.40060;141.69907;;
 
 14;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;4,7,1,0;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;15,14,9,8;,
 4;16,17,18,19;,
 4;16,19,8,11;,
 4;20,21,22,23;,
 4;20,23,12,15;,
 4;19,18,21,20;,
 4;24,25,19,20;,
 4;26,24,20,15;,
 4;25,27,8,19;;
 
 MeshMaterialList {
  3;
  14;
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
  2,
  2,
  2;;
  Material {
   0.000000;0.800000;0.263200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.511200;0.511200;0.511200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.006400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  5;
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000634;,
  0.000000;0.999999;0.001699;,
  0.000000;-0.001320;0.999999;;
  14;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;2,2,2,2;;
 }
 MeshTextureCoords {
  28;
  1.000000;0.227730;,
  0.000000;0.219610;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.789260;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.811060;,
  0.164020;0.227890;,
  0.000000;0.227730;,
  0.000000;0.000000;,
  0.164150;0.000000;,
  0.163610;1.000000;,
  0.000000;1.000000;,
  0.000000;0.789260;,
  0.163720;0.788830;,
  0.843840;0.000000;,
  1.000000;0.000000;,
  1.000000;0.228700;,
  0.843960;0.228550;,
  0.844270;0.787060;,
  1.000000;0.786660;,
  1.000000;1.000000;,
  0.844380;1.000000;,
  0.844270;0.787060;,
  0.843960;0.228550;,
  0.163720;0.788830;,
  0.164020;0.227890;;
 }
}
