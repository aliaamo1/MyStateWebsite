#!/usr/bin/perl
use strict;
use CGI ':standard';

my $name= param('name');
my $userName= param('user');
my $pWord= param('password');

print "Content-type: text/html\n\n";
print "<html>";
print "<head>";
#print "<title> Perl Script </title>";
print "</head>";

#print "Name is: $name <br> Username is: $userName <br> Password is: $pWord <br>\n";

my $file= 'members.csv';
open(INFO, "<$file") or die "Cannot open $file";

my @lines = <INFO>;
my $exists = 0;
	foreach my $line (@lines)
	{
		chomp( $line);
		my ($fileName, $fileUname, $filePword, $friends) = split(',', $line);
	#CHECKS IF THE USERNAME ENTERED ALREADY EXISTS
		if($fileUname eq $userName)
		 {	print "<h2> REGISTRATION FAILURE </h2>";
			print "Username: $userName exists <br>";
			print "<a name=label></a>";
	       	 print "<a href=http://www.cs.mcgill.ca/~amohar/registration.html#label>Click here to register.</a>";
       		$exists=1;
		 exit;
		}
		print "\n";
	}
close(INFO);

	if($exists == 0) 
	{
		my $lineTOfile = "$name".','."$userName".','."$pWord".',';
#		print $lineTOfile;
	#CHECKS IF FILE IS EMPTY
		if(-z $file)
		{ 
			open(APP,">$file");
		}
		else 
		{
			open(APP,">>$file");
		}	
			print APP "$lineTOfile\n";
			close(APP);
			 print "<h2>SUCCESS! YOU ARE NOW A MEMBER!</h2>";
                         print "<a name=label></a>";
                         print "<a href=http://www.cs.mcgill.ca/~amohar/triWel.html#label>Click here to login.</a>";		
	}
#}
#while(my $line = <INFO>)
#{
#	chomp( $line); #removes carriage return from between lines
#	print ($line);
#}
#my $line = <INFO>;
#my @linebyline = split(/\n/, my $line);
#print @linebyline;


#print $lines[0];
#close(INFO);

print "</body>";
print "</html>";
