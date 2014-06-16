% intersect.pl
% ex: set ft=prolog:
% Evaluates whether a pair of line segments in a plane intersect at a point
% Ignores lines that are colinear
%
% Possible places for improvement:
%   1. Generalize to N dimensions
%   2. Allow csv (comma-separated values) input using SWI-Prolog's csv module
%   3. Remove colinearity exception/make separate case

% Note: these points should be integers; multiply by a power of 10 if necessary
% (Prolog's floating point evaluation isn't the best)
line(a, [ -250,     50], [   350,     50]).
line(b, [ -223,   9999], [  -210,  -5623]).
line(c, [ -123,   9999], [  -110,  -5623]).
line(d, [10010, 100034], [200023, 210023]).
line(e, [  150,   -100], [   150,    100]).
line(f, [  200,    200], [   300,    200]).
line(g, [  250,     50], [   250,    200]).
% Add more lines here

intersects(J,K,[X,Y]) :-
    line(J,[Ax,Ay],[Bx,By]),
    line(K,[Cx,Cy],[Dx,Dy]),
    locale_sort([J,K],[J,K]), % Needed to prevent repeats like L1,L2 + L2,L1
    [Ex,Ey] is [Bx-Ax,By-Ay],
    [Fx,Fy] is [Dx-Cx,Dy-Cy],
    Divisor is Ex*Fy - Fx*Ey,
    Divisor \== 0, % Rules out colinear lines
    H is ((Ay-Cy)*Ex - (Ax-Cx)*Ey) / Divisor,
    H =< 1,
    H >= 0,
    [X,Y] is [Cx+Fx*H, Cy+Fy*H].

no_intersects(L) :-
    line(L,_,_),
    \+ (intersects(L,_,_)),
    \+ (intersects(_,L,_)).

/*
 * Example usage:
 * intersects(a,b,[X,Y]).     % Determine whether a and b intersect and where
 * intersects(a,K,[X,Y]).     % Find all lines K that intersect with line 'a'
 * intersects(J,K,[250,200]). % Find all lines J and K that intersect at 250,200
 * intersects(J,K,[X,50]).    % Find all lines J and K that intersect at Y=50
 * intersects(J,K,[X,Y]).     % Find all intersecting lines and their intersects
 */
