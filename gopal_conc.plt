#set si sq
set pm3d map
set size ratio 2.0
#set palette rgbform 33,13,10
#set zran [-1:1]
#set xran [10:90]
#set yran [10:90]

list = system('ls Final_Conc_Profile.*')
i = 1
do for [file in list] {
ipname = sprintf ('%s', file)
sp ipname us 1:2:3 notitle
i = i + 1
}

