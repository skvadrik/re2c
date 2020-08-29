#!/usr/bin/env perl
use 5.012;
use warnings;
use Getopt::Long;

=head1 NAME

C<gen_datetime.pl> - Generates timestamps

=head1 USAGE

Generate a 250mb file:

    gen_datetime.pl

Generate file of the specified size:

    gen_datetime.pl -s 250000000

=cut

sub rand_range {
    my ($min, $max) = @_;
    return $min + int(rand($max - $min + 1));
}

sub gen_timezone {
    return "Z" if rand() < 0.3;

    return sprintf("%s%02d:%02d",
                   rand() < 0.5 ? "+" : "-",
                   rand_range(0, 23),
                   rand_range(0, 59));
}

sub gen_date {
    return sprintf("%d-%02d-%02dT%02d:%02d:%02d%s",
                   rand_range(1000, 9999),
                   rand_range(1, 12),
                   rand_range(1, 31),
                   rand_range(0, 23),
                   rand_range(0, 59),
                   rand_range(0, 59),
                   gen_timezone);
}

# Number of bytes emitted (approximately)
my $b = 100000000; # ~100mb
GetOptions("size_bytes=i" => \$b);

open(my $fh, '>', 'big');

while (1) {
    my $d = gen_date;
    $b -= length($d) if defined $b;
    printf $fh "%s\n", gen_date;
    last if (defined $b && $b <= 0);
}

close($fh)
