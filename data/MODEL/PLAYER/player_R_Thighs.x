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
 19;
 0.08290;-0.05755;-6.14103;,
 3.84538;-0.05755;-8.15281;,
 3.48585;-11.13712;-6.35641;,
 0.08290;-11.13712;-5.98130;,
 3.82802;-0.05755;-0.11435;,
 3.74820;-11.13712;-0.11435;,
 3.78798;-0.05755;7.51627;,
 3.42845;-11.13712;7.00471;,
 0.08290;-0.05755;5.75258;,
 0.08290;-11.13712;5.75258;,
 -3.74909;-0.05755;3.68314;,
 -3.74909;-11.13712;3.68314;,
 -3.61455;-0.05755;-0.11437;,
 -3.61455;-11.13712;-0.11437;,
 -3.74095;-0.05755;-4.00914;,
 -3.74095;-11.13712;-4.00914;,
 0.08290;-0.05755;-6.14103;,
 0.08290;-11.13712;-5.98130;,
 0.08290;-0.05755;-0.11435;;
 
 9;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;;
 
 MeshMaterialList {
  4;
  9;
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
  0.000000;1.000000;0.000000;,
  -0.385556;-0.039300;-0.921847;,
  -0.294405;-0.071898;-0.952973;,
  0.999801;-0.019799;0.002571;,
  0.999487;-0.019941;0.025063;,
  -0.433319;-0.006948;0.901214;,
  -0.475178;0.000000;0.879890;,
  -0.999999;0.000000;-0.001486;,
  -0.999474;0.000000;0.032437;,
  0.999609;-0.019647;-0.019923;,
  -0.390482;-0.013880;0.920506;,
  -0.999373;0.000000;-0.035406;,
  -0.472720;-0.006296;-0.881190;;
  9;
  4;1,2,2,1;,
  4;9,3,3,9;,
  4;3,4,4,3;,
  4;10,5,5,10;,
  4;5,6,6,5;,
  4;11,7,7,11;,
  4;7,8,8,7;,
  4;12,1,1,12;,
  3;0,0,0;;
 }
 MeshTextureCoords {
  19;
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
  0.062500;0.000000;;
 }
}
