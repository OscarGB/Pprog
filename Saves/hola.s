#p:1|Player|1|
#s:1|Entrance|-1|1|3|-1|-1|-1|TRUE|This is the beginning of your adventure. There's a door at the east.|+------------+|            |+--+         |   |         (   |         (   |         |   +|  |-----+//
#s:2|Closed_space|-1|-1|2|1|-1|-1|FALSE|This space was closed and dark... There's a door at the west.|+------------+|            ||            |)            |)            ||            |+---|**|-----+//
#s:3|Objects|-1|4|-1|-1|-1|-1|FALSE|There are some objects on the ground...|+---+         |   +--------+|            ||            -|            _|            |+------------+//
#s:4|Ladder|3|5|-1|4|10|-1|FALSE|There's an uncomplete_ladder...|+---|  |-----+|            ||         =  |-        =   -_            _|            |+------------+//
#s:5|Wall_south|2|-1|6|5|-1|-1|FALSE|There's a wall at the north.|+---|**|-+    |        |    |        +---+-            |_            ||            |+---|  |-----+//
#s:6|Casilla|-1|-1|-1|-1|-1|8|FALSE|There's a ladder|+------------+|            ||        =   ||         =  ||            ||            |+------------+//
#s:7|Casilla|6|-1|-1|7|-1|-1|FALSE|You can see... A penguin!|+---|  |-----+|            ||            |-            |_            |+------------+              //
#s:8|Casilla|-1|7|8|-1|-1|-1|FALSE|The exit is near...|                               +---------+   |         -   |         _   |         |   +|  |-----+//
#s:9|Casilla|-1|9|-1|-1|-1|-1|FALSE|EXIT|+------------+|            |+--+   EXIT  |   |         (   |         (   |         |   +---------+//
#s:10|Casilla|8|-1|-1|9|-1|-1|FALSE|The exit is behind a door with a lobster image...|+---|  |-----+|            ||            |)            |)            ||      +-----++------+      //
#l:1|1|2|door|CLOSEDL|
#l:2|2|5|wall|CLOSEDL|
#l:3|1|4|Door3|OPENL|
#l:4|3|4|Door4|OPENL|
#l:5|4|5|Door5|OPENL|
#l:6|5|7|Door6|OPENL|
#l:7|7|8|Door7|OPENL|
#l:8|8|10|Door8|OPENL|
#l:9|9|10|exit|CLOSEDL|
#l:10|4|6|uncomplete_ladder|CLOSEDL|
#o:0|0|name|desc|mdesc|s|FALSE|0|FALSE|FALSE|FALSE|0|0|
#o:1|1|lantern|A little lantern|Try to turn it on|L|TRUE|1|FALSE|TRUE|FALSE|-1|10|
#o:2|1|Plus|A plus, don't use it. Absolutely unusable.|This wasn't here|+|FALSE|1|FALSE|FALSE|FALSE|-1|-1|
#o:3|1|littleO|This is a little o|It may not help you|o|TRUE|1|FALSE|FALSE|FALSE|-1|-1|
#o:4|3|At|This is an at|It may not help you|@|TRUE|3|FALSE|FALSE|FALSE|-1|-1|
#o:5|2|Key|This is a key|Try to open a door with it|K|TRUE|2|FALSE|FALSE|FALSE|1|-1|
#o:6|3|Tnt|This is TNT|Try to open a wall with it|t|TRUE|3|FALSE|FALSE|FALSE|2|-1|
#o:7|2|Stone|This is a heavy stone|This is a moved stone|s|FALSE|2|FALSE|FALSE|FALSE|-1|-1|
#o:8|2|Ladder|This is a ladder|Try to open the uncomplete_ladder with it|=|TRUE|2|FALSE|FALSE|FALSE|10|-1|
#o:9|3|Minus|This is a positive minus (he's happy)|This is a moved positive minus|-|FALSE|3|FALSE|FALSE|FALSE|-1|-1|
#o:10|5|Lobster|This is a lobster|This is a moved lobster (And may be THE key)|l|TRUE|5|FALSE|FALSE|FALSE|9|-1|
#o:11|5|Important thing|This is an important thing (not SO important)|This is a moved important thing|i|FALSE|5|FALSE|FALSE|FALSE|-1|-1|
#o:12|6|Non important thing|This is a non important thing|Why have you picked that?|n|TRUE|6|FALSE|FALSE|FALSE|-1|-1|
#o:13|8|Most important key|This is the MOST IMPORTANT KEY|It seems to be broken...|m|TRUE|8|FALSE|FALSE|FALSE|-1|-1|
#o:14|10|Trophy|This is a trophy|You are the best!|T|TRUE|10|FALSE|FALSE|FALSE|-1|-1|
#o:15|9|Exit|This is the exit|This is a moved exit|e|FALSE|9|FALSE|FALSE|FALSE|-1|-1|
#o:16|8|Penguin|This is a penguin. It could kill you.|This is a moved penguin|p|FALSE|8|FALSE|FALSE|FALSE|-1|-1|
#o:17|8|Money|A coin!|You're rich|$|TRUE|8|FALSE|FALSE|FALSE|-1|-1|
#o:18|7|Euros|A coin!|You're rich|E|TRUE|7|FALSE|FALSE|FALSE|-1|-1|
#o:19|4|federal cop|He's looking you in a suspicious way...|He's looking you in a suspicious way...|f|FALSE|4|FALSE|FALSE|FALSE|-1|-1|
#o:20|4|Pprog|Best subject ever!|Muajajajaja|P|FALSE|4|FALSE|FALSE|FALSE|-1|-1|
