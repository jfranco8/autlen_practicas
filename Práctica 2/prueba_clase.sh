make clean
make
./prueba_clase
dot -Tpng afd.dot > pruebas/prueba_clase.png
dot -Tpng prueba_clase.dot > originales/prueba_clase.png
make clean
