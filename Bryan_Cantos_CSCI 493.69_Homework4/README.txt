i) s1, s2, s3, s4 and  the written homework were completed

ii) S4 does not compute the Albedo correctly

iii) Type <make all> to compile everything. To run them, type 
		./s1 <INPUT_PGM_IMAGE> <THERSHOLD> <OUTPUT_PARAMETERS_FILE>
		./s2 <INPUT_PARAMETER_FILE> <IMAGE1> <IMAGE2> <IMAGE3> <OUTPUT_DIRECTION_FILE>
		./s3 <INPUT_DIRECTION_FILE> <IMAGE1> <IMAGE2> <IMAGE3> <STEP> <THERSHOLD> <OUTPUT>
        ./s4 <INPUT_DIRECTION_FILE> <IMAGE1> <IMAGE2> <IMAGE3> <THERSHOLD> <OUTPUT>

iv) Inputs files
        s1 - <INPUT_PGM_IMAGE> <THERSHOLD>
        s2 - <INPUT_PARAMETER_FILE> <IMAGE1> <IMAGE2> <IMAGE3>
        s3 - <INPUT_DIRECTION_FILE> <IMAGE1> <IMAGE2> <IMAGE3>
        s4 - <INPUT_DIRECTION_FILE> <IMAGE1> <IMAGE2> <IMAGE3>

    Output files
        s1 - <OUTPUT_PARAMETERS_FILE>
        s2 - <OUTPUT_DIRECTION_FILE>
        s3 - <OUTPUT_PGM>
        s4 - <OUTPUT_PGM>

v) The formula I used for s2 is: sqrt( ( radius * radius ) - ( nX * nX ) - ( nY * nY ) )