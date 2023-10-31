#converts all *grain_id.txt to png

set si sq
set pm3d map
unset colorbox
unset border
unset tics
set term png size 1920,1440

list = system('ls Final_Conc_Profile.*')
i = 1
do for [file in list] {
ipname = sprintf ('%s', file)
opname = sprintf ('%s_comp.png', file)
set out 'comp'.i.'.png'
sp ipname us 1:2:3 notitle
i = i + 1
}


