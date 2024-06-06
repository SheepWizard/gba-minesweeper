OUTPATH="source/assets"
ASSETS="../../assets"

rm -rf $OUTPATH
mkdir -p $OUTPATH
cd $OUTPATH

grit $ASSETS/cell_hidden.bmp -gb -gu16
grit $ASSETS/cell_1.png -gb -gu16
grit $ASSETS/cell_2.png -gb -gu16
grit $ASSETS/cell_3.png -gb -gu16
grit $ASSETS/cell_4.png -gb -gu16
grit $ASSETS/cell_5.png -gb -gu16
grit $ASSETS/cell_6.png -gb -gu16
grit $ASSETS/cell_7.png -gb -gu16
grit $ASSETS/cell_8.png -gb -gu16
grit $ASSETS/cell_open.bmp -gb -gu16
grit $ASSETS/cell_mine.bmp -gb -gu16
grit $ASSETS/cell_flag.bmp -gb -gu16
grit $ASSETS/cell_minehit.bmp -gb -gu16
grit $ASSETS/cell_wrongflag.bmp -gb -gu16