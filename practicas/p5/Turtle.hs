module Turtle where
import SVG

-- Posicion en coordenadas (x,y)
type Position = (Float,Float)
-- Orientacion de la tortuga, se supone en grados
type Heading  = Float
-- Turtle = (paso,giro,posicion,orientacion)
type Turtle   = (Float,Float,Position,Heading)

data Move     = Forward | TurnLeft | TurnRight

-- Devuelve un nuevo estado de la tortuga,
-- según el movimiento deseado.
-- Los datos de paso y giro no cambian.
moveTurtle :: Turtle -> Move -> Turtle
moveTurtle (paso,giro,(x,y),orn) Forward = (paso,giro,(x+paso*c,y+paso*s),orn)
  where
    ornrad = (pi/180.0)*orn
    c = cos ornrad
    s = sin ornrad
moveTurtle (paso,giro,pos,orn) TurnLeft  = (paso,giro,pos,orn+giro)
moveTurtle (paso,giro,pos,orn) TurnRight = (paso,giro,pos,orn-giro)

tplot :: Turtle -> String -> [Position]
tplot (paso,giro,(x,y),orn) [] = [(x,y)]
tplot (paso,giro,(x,y),orn) (z:zs) =  if z == '>' then (x,y) : tplot ( moveTurtle (paso,giro,(x,y),orn) Forward ) (zs)
                                      else if z == '+' then (x,y) : tplot ( moveTurtle (paso,giro,(x,y),orn) TurnRight ) (zs)
                                      else if z == '-' then (x,y) : tplot ( moveTurtle (paso,giro,(x,y),orn) TurnLeft ) (zs)
                                      else tplot (paso,giro,(x,y),orn) (zs)