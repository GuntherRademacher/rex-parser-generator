# This file was generated on Mon Nov 1, 2021 16:07 (UTC+01) by REx v5.54 which is Copyright (c) 1979-2021 by Gunther Rademacher <grd@gmx.net>
# REx command line: HelloWorld.ebnf -name HelloWorld_REx_11 -cpp -rex -main -trace

#option nogrammar
#option noabbreviations
#option noambiguities
#option classify
#option case-sensitive
#option nosymbols
#option trace
#option cpp
#option class="HelloWorld_REx_11"

# lookahead sets

# set 0
          [W, 2];
# set 1
          [W, 3];

W (1)
        : ( [' '] ) + ;
(2)
        : "hello" ;
(3)
        : "world" ;

# End
