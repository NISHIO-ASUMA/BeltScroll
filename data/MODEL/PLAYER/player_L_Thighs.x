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
 26;
 -0.50908;0.16959;-6.01534;,
 3.86751;0.16959;-3.69796;,
 3.86751;-10.98815;-3.33174;,
 -0.50908;-10.98815;-6.01534;,
 3.86992;0.16959;0.40420;,
 3.86992;-10.98815;0.39954;,
 3.85782;0.16959;3.91631;,
 3.39846;-10.98815;3.95379;,
 -0.50908;0.16959;5.93031;,
 -0.50908;-10.98815;5.93031;,
 -3.87343;0.16959;7.73174;,
 -3.42110;-10.98815;7.30874;,
 -3.66140;0.16959;0.40420;,
 -3.83632;-10.98815;0.40420;,
 -3.84676;0.16959;-7.74227;,
 -3.54852;-10.98815;-5.93374;,
 -0.50908;0.16959;-6.01534;,
 -0.50908;-10.98815;-6.01534;,
 -0.50908;-10.98815;0.40420;,
 -0.50908;-10.98815;0.40420;,
 -0.50908;-10.98815;0.40420;,
 -0.50908;-10.98815;0.40420;,
 -0.50908;-10.98815;0.40420;,
 -0.50908;-10.98815;0.40420;,
 -0.50908;-10.98815;0.40420;,
 -0.50908;-10.98815;0.40420;;
 
 16;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,3,2;,
 3;19,2,5;,
 3;20,5,7;,
 3;21,7,9;,
 3;22,9,11;,
 3;23,11,13;,
 3;24,13,15;,
 3;25,15,17;;
 
 MeshMaterialList {
  4;
  16;
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
  13;
  0.362720;-0.041227;-0.930986;,
  0.495529;-0.013993;-0.868479;,
  0.999388;-0.010119;0.033498;,
  0.997510;-0.020215;0.067570;,
  0.442621;-0.007121;0.896680;,
  0.450067;-0.007144;0.892966;,
  -0.999967;-0.007790;0.002133;,
  -0.999929;-0.003688;-0.011316;,
  0.000000;-1.000000;-0.000000;,
  1.000000;-0.000010;-0.000617;,
  0.435145;-0.007096;0.900333;,
  -0.999808;-0.011891;0.015581;,
  0.221828;-0.067541;-0.972744;;
  16;
  4;0,1,1,0;,
  4;9,2,2,9;,
  4;2,3,3,2;,
  4;10,4,4,10;,
  4;4,5,5,4;,
  4;11,6,6,11;,
  4;6,7,7,6;,
  4;12,0,0,12;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;;
 }
 MeshTextureCoords {
  26;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
