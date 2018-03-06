#########################################
#    CSCI 315 - Programming Lab #1      #
#                                       #
#    Jasmine Lee                        #
#    jlee173@mail.csuchico.edu          #
#                                       #
#########################################
my $name = "Jasmine Lee";

#########################################
##
##  ETHICS Reminder
##
##  Yes: use the internet to learn Perl
##
##  No: don't use other people to do your work
##
#########################################

#########################################
# VARIABLE DEFINITIONS
#########################################

# pseudo-constants...
# ... the tests override your choice, so
#     you can set your preferred value
my $STOP_WORDS = 0;           # flag - filter stopwords,  0 (off) | 1 (on)
my $DEBUG = 0;                # flag - print debug words, 0 (off) | 1 (on)
my $SEQUENCE_LENGTH = 10;     # length of song title, suggested default 10

# variable initialization...
# ... you will use all three at some point

# array of song tracks
my @tracks = ();
# hash of hashes for bigram counts
my %counts = ();
# hash of words already used in current sequence, reset for new sequence
my %word_history = ();


#########################################
# Functions that you will edit
#########################################

# This extracts a title from the raw track input line
sub extract_title{
    if ($DEBUG){print "<extracting titles>\n";}
    my @tracktitles = ();

    foreach my $track (@tracks) {

        ##########
        # TASK 1 #
        ##########
        ## Edit the regex below to capture only song title
        ##
        if ($track =~ /.*<SEP>(.*)$/){
        ##
        ############################# End Task 1

            # $1 should be the title caught by regex first set of parens
            # It is added to end of the array
            push @tracktitles, $1;
        }
    }
    # Updates @tracks
    return @tracktitles;
}



# This removes comments and parenthetical information
sub comments{
    if ($DEBUG){print "<filtering comments>\n";}
    my @filteredtitles = ();


    # This loops through each track
    foreach my $title (@tracks) {

        ##########################
        # TASK 2 #
        ##########################
        ## Add regex substitutions to remove superflous comments and all that follows them
        ##########################


        ##########################
        ##

				$title =~ s/\(.*//;
				$title =~ s/\[.*//;
				$title =~ s/\{.*//;
				$title =~ s/\\.*//;
				$title =~ s/\/.*//;
				$title =~ s/_.*//;
				$title =~ s/\-.*//;
				$title =~ s/:.*//;
				$title =~ s/\".*//;
				$title =~ s/`.*//;
				$title =~ s/\+.*//;
				$title =~ s/=.*//;
				$title =~ s/feat\..*//;

				##                      ##
        ##########################

        ########################## End Task 2

        # Add the edited $title to the new array of titles
        push @filteredtitles, $title;
    }
    # Updates @tracks
    return @filteredtitles;
}



# This removes punctutation
sub punctuation{
    if ($DEBUG){print "<filtering punctuation>\n";}
    my @filteredtitles = ();

    ##########################
    # TASK 3 #
    ##########################
    ## Add regex substitutions to remove punctuation
    ## Remember to permit the apostrophe ' (near enter)
    ## Use the g (greedy) directive
    ## You need to write the loop (hint it's same one used in Task 2)
    ## Make sure to add you edited title to the new @filteredtitles array,
    ##    which replaces @tracks when returned.
    ##########################


    ##########################
    ##                      ##

	  # This loops through each track
    foreach my $title (@tracks) {
			
			$title =~ s/\?//g;
			$title =~ s/¿//g;
			$title =~ s/!//g;
			$title =~ s/¡//g;
			$title =~ s/\.//g;
			$title =~ s/;//g;
			$title =~ s/://g;
			$title =~ s/&//g;
			$title =~ s/\$//g;
			$title =~ s/\*//g;
			$title =~ s/\@//g;
			$title =~ s/%//g;
			$title =~ s/#//g;
			$title =~ s/\|//g;

      push @filteredtitles, $title;
    }


    ##                      ##
    ##########################

    ########################## End Task 3

    # Updates @tracks
    return @filteredtitles;
}



# This removes non-English characters, trailing whitespace, and blank titles
sub clean{
    if ($DEBUG){print "<filtering non-ASCII characters>\n";}
    my @filteredtitles = ();


    ##########################
    # TASK 4, 5, 6, 7 Below  #
    ##########################
    ## These are small tasks, where each "<your code here>"
    ##   will be either a regex substitution
    ##   or an if statement and a subsequent action (e.g. skip to next without adding)
    ##########################


    # This loops through each track
    foreach my $title (@tracks) {


        ##########################
        # TASK 4 #
        ##########################
        ## Add regex substitutions to trim leading and trailing whitespace
        ##    and leading and trailing apostrophes.
        ##########################

        # replace leading/trailing apostrophe

				$title =~ s/^'+|'+$//g;

        # trim whitespace on either end

				$title =~ s/(^\s*|\s*$)//g;

        ########################## End Task 4



        ##########################
        # TASK 5 #
        ##########################
        ## Filter out non-ASCII characters
        ## (letters, numbers, apostophe allowed)
        ##########################

        # skip title if contains any single non-English character
				
				$title =~ /[^a-zA-Z0-9 '\s]/ and next;

        ########################## End Task 5



        ##########################
        # TASK 6 #
        ##########################
        ## Skip title is blank, contains only whitespace,
        ## or contains only apostrophe
        ##########################

        # skip if only contains only an apostrophe

				$title =~ /^'*$/ and next;

        # skip if only contains whitespace
				
				$title =~ /^\s*\n/ and next;


        ########################## End Task 6



        ##########################
        # TASK 7 #
        ##########################
        ## Set to lowercase
        ##########################
        # minor edit needed to this line (perl has a handy function)
				$title = lc $title;
        push @filteredtitles, $title;
        ########################## End Task 7

    }
    # Updates @tracks
    return @filteredtitles;
}

# This removes common stopwords
sub stopwords{
    if ($DEBUG){print "<filtering stopwords>\n";}
    my @filteredtitles = ();

    ##########################
    # TASK 8 #
    ##########################
    ## Add regex substitutions to remove common stopwords
    ## Loop like before
    ## Use \b (word boundaries) in your regexs
    ##########################


    ##########################
    ##                      ##
    foreach my $title (@tracks) {

		$title =~ s/\ba\b\s//g;
		##$title =~ s/\ban\b\s//g;
		##$title =~ s/\band\b\s//g;
		##$title =~ s/\bby\b\s//g;
		##$title =~ s/\bfor\b\s//g;
		##$title =~ s/\bfrom\b\s//g;
		##$title =~ s/\bin\b\s//g;
		##$title =~ s/\bof\b\s//g;
		##$title =~ s/\bon\b\s//g;
		##$title =~ s/\bor\b\s//g;
		##$title =~ s/\bout\b\s//g;
		##$title =~ s/\bthe\b\s//g;
		##$title =~ s/\bto\b\s//g;
		##$title =~ s/\bwith\b\s//g;
		
		
		
    push @filteredtitles, $title;
		}
		##                      ##
    ##########################
    print "$name has not yet implemented filter stopwords.\n";  # delete when earned


    ########################## End Task 8

    # Updates @tracks
    return @filteredtitles;
}


# This splits the tracks into words and builds the bi-gram model
sub build_bigrams{

    ##########################
    # TASK: Bigram Counts
    ##########################
    ## Loop through the tracks to split the titles into words.
    ## Count all adjacent pairs.
    ##
    ## Following your diligent work, the %counts hash (declared up yonder)
    ## should contain the bigram counts for all consecutive word pairs across
    ## the entire dataset of tracks
    ##
    ## Plan carefully.  It is not a lot of code.
    ##
    ## My approach is 10 lines (4 of which are just a closing curly-brace)
    ##    (the take away is that it does not take much;
    ##     there is no need to take exactly 10 lines)
    ##########################


    ##########################
    ##                      ##

		foreach my $title (@tracks) {

		my @sepWords = split(' ', $title);
		if(scalar @sepWords > 1) {

		while (scalar @sepWords 			
			


    ##                      ##
    ##########################
    print "$name has not yet implemented build_bigrams.\n";  # delete when earned
    ########################## End Task Bigram Counts

    if ($DEBUG){print "<bigram model built>\n";}
}


# This finds the most-common-word (mcw) to follow the given word
sub mcw{
    # Seed word (arg) for which we find the next word
    my $word = $_[0];
    # Store the most common next word in this variable and return it.
    my $best_word = '';

    ##########################
    # TASK: MCW
    ##########################
    ##
    ## Find all available "next" words for $word
    ## Sort them (there's a function for that),
    ##   so your results are deterministic and match the tests
    ##
    ## Iterate through all the available words
    ##   that follow $word in the %counts
    ##
    ## Remember to check the %word_history
    ##   and skip that word if used before
    ##
    ## Find the candidate word with highest count,
    ##   update $best_word (it gets returned)
    ##
    ## In case of ties, stick with first one found
    ##    (i.e. use strictly > in your count comparison if)
    ##    that way you make the same choice the tests do
    ##
    ## This comment is longer than your code will be for this task.
    ##########################


    ##########################
    ##                      ##
    ## <Insert code here>   ##
    ##                      ##
    ##########################
    print "$name has not yet implemented mcw.\n";  # delete when earned
    ########################## End Task MCW


    if ($DEBUG){print "  <mcw for \'$word\' is \'$best_word'\>\n";}

    # return the most common word to follow $word
    return $best_word
}



# This builds a song title based on mcw
sub sequence{
    if ($DEBUG){print "<sequence for \'$_[0]\'>\n";}

    # clear word history for new sequence
    %word_history = ();

    ##########################
    # TASK: Build Song Title
    ##########################
    ## Use the seed word to build a sequence.
    ## For each word, look up the mcw
    ## Add to sequence.
    ## Repeat until next word is empty or newline
    ## Mind the max $SEQUENCE_LENGTH
    ## Remember to track word history using %word_history
    ## My solution is about 12 lines (and could have been less)
    ##########################


    ##########################
    ##                      ##
    ## <Insert code here>   ##
    ##                      ##
    ##########################
    print "$name has not yet implemented sequence.\n";  # delete when earned

    # return the sequence you created instead of this measely string
    return "[ERROR: SEQUENCE 404]";
    ########################## End Task Song Title
}

##############################################################################
##             End Functions that students edit                              #
##############################################################################

##############################
##                           #
##     READ ONLY BELOW       #
##                           #
##############################

##############################
##############################
##############################
##                           #
##     Menu System           #
##                           #
##############################
##                           #
##  Read and understand      #
##   how to use the commands #
##                           #
##  You do not need to edit  #
##    the menu code below.   #
##                           #
##  You may expand the menu  #
##   to you add your own     #
##   commands, if desired.   #
##                           #
##  Do not break any of the  #
##   existing command rules  #
##   or you will fail tests. #
##                           #
##############################

# This is the "command" loop that runs until end-of-input
foreach $line ( <STDIN> ) {
    # read a line from standard input
    chomp( $line );  # yummy!

    # split line into array of words
    @input = split(/\s+/, $line);
    # command is $input[0], first word
    $command = lc($input[0]);
    # argument is $input[1], second word

    if ($command eq "load"){
        # load the input file
        load($input[1]);
    }elsif ($command eq "length"){
        # change the sequence length
        if ($DEBUG){print "<sequence length " . $input[1] . ">\n";}
        $SEQUENCE_LENGTH = $input[1];
    }elsif ($command eq "debug"){
        # toggle debug mode on/off
        if (lc($input[1]) eq "on"){
            if ($DEBUG){print "<debug on>\n";}
            $DEBUG = 1;
        }elsif (lc($input[1]) eq "off"){
            if ($DEBUG){print "<debug off>\n";}
            $DEBUG = 0;
        }else{
            print "**Unrecognized argument to debug: " . $input[1] . "\n";
        }
    }elsif ($command eq "count"){
        if (lc($input[1]) eq "tracks"){
            # count the number of lines in @tracks
            count_lines(@tracks);
        }elsif (lc($input[1]) eq "words"){
            # count the number of words in @tracks
            count_words(@tracks);
        }elsif (lc($input[1]) eq "characters"){
            # count the number of characters in @tracks
            count_characters(@tracks);
        }else{
            print "**Unrecognized argument to count: " . $input[1] . "\n";
        }
    }elsif ($command eq "stopwords"){
        # toggle stopwords on/off
        if (lc($input[1]) eq "on"){
            if ($DEBUG){print "<stopwords on>\n";}
            $STOP_WORDS = 1;
        }elsif (lc($input[1]) eq "off"){
            if ($DEBUG){print "<stopwords off>\n";}
            $STOP_WORDS = 0;
        }else{
            print "**Unrecognized argument to stopwords: " . $input[1] . "\n";
        }
    }elsif ($command eq "filter"){
        if ($input[1] eq "title"){
            # extract the title from the line
            @tracks = extract_title();
        }elsif ($input[1] eq "comments"){
            # filter out extra phrases from the titles
            @tracks = comments();
        }elsif ($input[1] eq "punctuation"){
            # filter out punctuation
            @tracks = punctuation();
        }elsif ($input[1] eq "unicode"){
            # filter out non-ASCII characters
            @tracks = clean();
        }elsif ($input[1] eq "stopwords" && $STOP_WORDS){
            # filter out common words, if enabled
            @tracks = stopwords();
        }else{
            print "**Unrecognized argument to stopwords: " . $input[1] . "\n";
        }
    }elsif ($command eq "preprocess"){
        # preprocess does all of the filtering tasks at once and builds bigrams

        # first, extract the title from the line
        @tracks = extract_title();
        # next, filter out extra phrases from the titles
        @tracks = comments();
        # next, filter out punctuation
        @tracks = punctuation();
        # next, filter out non-ASCII characters, blank titles
        @tracks = clean();
        # next, filter out common words, if enabled
        if ($STOP_WORDS){@tracks = stopwords();}

        # build bi-gram model counting occurences of word pairs
        build_bigrams();
    }elsif ($command eq "build"){
        # build bi-gram model counting occurences of word pairs
        build_bigrams();
    }elsif ($command eq "mcw"){
        # print the most-common-word to follow given word
        print mcw(lc($input[1])) . "\n";
    }elsif ($command eq "sequence"){
        # print a song title based on the given word
        print sequence(lc($input[1])) . "\n";
    }elsif ($command eq "print"){
        # print the tracks array to standard out
        if ($input[1] > 0){
            print_some_tracks($input[1]);
        }else{
            print_all_tracks(@tracks);
        }
    }elsif ($command eq "author"){
        print "Lab1 by $name\n";
    }elsif ($command eq "name"){
        print sequence(lc($name))."\n";
    }elsif ($command eq "random"){
        print sequence((keys %counts)[rand keys %counts])."\n";
    }else{
        # warn user if command was ignored
        print "**Unrecognized command: " . $command . "\n";
    }
}


##############################
##############################
##############################
##                           #
##     Helper Functions      #
##                           #
##############################
##                           #
## Below contains important  #
## functions the menu uses.  #
##                           #
##                           #
## Feel free to look around. #
##                           #
## Help yourself to the      #
##     cookies and punch.    #
##                           #
## Look but don't touch.     #
##                           #
## You break it,             #
##         you bought it!    #
##############################


# This loops through N lines of the array
sub print_some_tracks{
    my $n = $_[0];
    if ($DEBUG){print "<printing $n$ tracks>\n";}
    for (my $i=0; $i < $n; $i++) {
        print $tracks[$i];
    }
}

# This loops through each line of the array
sub print_all_tracks{
    if ($DEBUG){print "<printing all tracks>\n";}
    # are you sure you want to? (use CTRL+C to kill it)
    foreach (@_) {print $_;} 
}

# Count lines of array
sub count_lines{
    if ($DEBUG){print "<counting number of tracks>\n";}
    print @_ . "\n";
}

# Count words, after splitting on whitespace
sub count_words{
    if ($DEBUG){print "<counting number of words>\n";}
    my $word_count = 0;
    foreach (@_) {
        @w = split(/\s+/, $_);
        $word_count += 0+@w;
    }
    print $word_count . "\n";
}

# Count individual characters
sub count_characters{
    if ($DEBUG){print "<counting number of characters>\n";}
    my $char_count = 0;
    foreach (@_) {
        $char_count += length($_);
    }
    print $char_count . "\n";
}

# Loads the tracks file into an array
sub load{
    open(INFILE, $_[0]) or die "Cannot open $_[0]: $!.\n";
    @tracks = <INFILE>;
    if ($DEBUG){print "<loaded " . $_[0] . ">\n";}
}
