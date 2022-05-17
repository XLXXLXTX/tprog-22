import Turtle
import SVG

main = do
 print $ "Practica 5"
 let
-- Graficos de tortuga
  figura = tplot (1,90,(0,0),0) ">+>+>+>"
-- Sistemas de Lindenmayer
  curva_kock = tplot (1,60,(0,0),0) (lsystem rule_curva_de_Kock "F" 3)
  curva_kock_cuadrada = tplot (1,90,(0,0),0) (lsystem rule_curva_de_Kock_cuadrada "F" 4)
  curva_kock_snowflake = tplot (1,60,(0,0),0) (lsystem rule_curva_de_Kock_SnowFlake "F++F++F" 3)
  curva_kock_snowflake_antisnowflake = tplot (1,60,(0,0),0) (lsystem rule_curva_de_Kock_Anti_SnowFlake "F++F++F" 6)
  minkowski = tplot (1,90,(0,0),0) (lsystem rule_Minkowski "F+F+F+F" 2)
  sierpinsky = tplot (1,120,(0,0),0) (lsystem rule_Triangulo_Sierpinsky "F-G-G" 3)
  sierpinsky_arrowhead = tplot (1,60,(0,0),0) (lsystem rule_Sierpinsky_Arrowhead "F" 6)
  curva_hilbert = tplot (1,90,(0,0),0) (lsystem rule_curva_de_Hilbert "f" 4)
  curva_gosper = tplot (1,60,(0,0),0) (lsystem rule_curva_de_Gosper "F" 3)

 savesvg "cuadrado" figura
 
 savesvg "kock" curva_kock
 savesvg "kock cuadrada" curva_kock_cuadrada
 savesvg "kock snowflake" curva_kock_snowflake 
 savesvg "kock anti-snowflake" curva_kock_snowflake_antisnowflake
 savesvg "minkowski" minkowski
 savesvg "sierpinsky" sierpinsky
 savesvg "sierpinsky arrowhead" sierpinsky_arrowhead
 savesvg "hilbert" curva_hilbert
 savesvg "gosper" curva_gosper

-------------------------------------------------------------------------------
-- FUNCIONES PARA GENERAR LAS FIGURAS
-------------------------------------------------------------------------------

aux :: (Char -> String) -> String -> String
aux _ [] = []
aux f (x:xs) = f x ++ (aux f xs)

lsystem :: (Char -> String) -> String -> Int -> String
lsystem f s v = if v == 0 then s 
                else if v > 0 then lsystem f (aux f s) (v-1) 
                else []

-------------------------------------------------------------------------------
-- REGLAS PARA LAS FIGURAS
-------------------------------------------------------------------------------
{--}
rule_curva_de_Kock :: Char -> String
rule_curva_de_Kock x = if x =='F' then "F+F--F+F"
                       else [x]

rule_curva_de_Kock_cuadrada :: Char -> String
rule_curva_de_Kock_cuadrada x = if x =='F' then "F+F-F-F+F"
                                else [x]


rule_curva_de_Kock_SnowFlake :: Char -> String
rule_curva_de_Kock_SnowFlake x = if x =='F' then "F-F++F-F"
                                 else [x]

rule_curva_de_Kock_Anti_SnowFlake :: Char -> String
rule_curva_de_Kock_Anti_SnowFlake x = if x =='F' then "F+F--F+F"
                                else [x]


rule_Minkowski :: Char -> String
rule_Minkowski x = if x =='F' then "F+F-F-FF+F+F-F"
                   else [x]

rule_Triangulo_Sierpinsky :: Char -> String
rule_Triangulo_Sierpinsky x = if x =='F' then "F-G+F+G-F" 
                              else if x == 'G' then "GG"
                              else [x]

rule_Sierpinsky_Arrowhead :: Char -> String
rule_Sierpinsky_Arrowhead x = if x =='F' then "G-F-G" 
                              else if x == 'G' then "F+G+F"
                              else [x]

rule_curva_de_Hilbert :: Char -> String
rule_curva_de_Hilbert x = if x =='f' then "-g>+f>f+>g-"
                          else if x == 'g' then "+f>-g>g->f+"
                          else [x]

rule_curva_de_Gosper :: Char -> String
rule_curva_de_Gosper x = if x =='F' then "F-G--G+F++FF+G-"
                         else if x == 'G' then "+F-GG--G-F++F+G"
                         else [x]
