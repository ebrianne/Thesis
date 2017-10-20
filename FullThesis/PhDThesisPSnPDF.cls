%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                                                                            %%
%% Class ``PhD Thesis PSnPDF''                                                %%
%%                                                                            %%
%% A PhD thesis LaTeX template for Cambridge University Engineering Department%%
%%                                                                            %%
%% Version: v1.4.1                                                            %%
%% Authors: Krishna Kumar                                                     %%
%% Date: 2013/11/16 (inception)                                               %%
%% License: MIT License (c) 2013 Krishna Kumar                                %%
%% GitHub Repo: https://github.com/kks32/phd-thesis-template/                 %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% ************************** Class Identification ******************************
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{PhDThesisPSnPDF}[2014/08/11 version 1.4.1 by Krishna Kumar]
\typeout{https://github.com/kks32/phd-thesis-template/}


% ******************************************************************************
% **************************** Class Definition ********************************
% ******************************************************************************

% *********************** Define a Print/Online Version ************************
\newif\if@print\@printfalse
\DeclareOption{print}{\@printtrue}

\newif\ifPHD@draft\PHD@draftfalse

% ****************************** Define index **********************************
\newif\ifPHD@index\PHD@indexfalse
\DeclareOption{index}{\PHD@indextrue}

% ******************************* Font Option **********************************
\newif\ifsetFont\setFontfalse                 % Font is not set

\newif\ifPHD@times\PHD@timesfalse             % Times with Math Support
\DeclareOption{times}{
\ifsetFont
\ClassWarning{PhDThesisPSnPDF}{Font selection conflict: A font package was
aleady specified. Please check the document class options in case you
have defined two fonts.}
\else
\PHD@timestrue
\setFonttrue
\fi
}

\newif\ifPHD@fourier\PHD@fourierfalse         % Fourier with Math Support
\DeclareOption{fourier}{
\ifsetFont
\ClassWarning{PhDThesisPSnPDF}{Font selection conflict: A font package was
aleady specified. Please check the document class options in case you
have defined two fonts.}
\else
\PHD@fouriertrue
\setFonttrue
\fi
}

\newif\ifsetCustomFont\setCustomFontfalse     % Custom Font with Math Support
\DeclareOption{customfont}{
\ifsetFont
\ClassWarning{PhDThesisPSnPDF}{Font selection conflict: A font package was
aleady specified. Please check the document class options in case you
have defined two fonts.}
\else
\setCustomFonttrue
\setFonttrue
\fi
}

% ******************************* Bibliography *********************************
\newif\ifsetBib\setBibfalse                   % Custom Bibliography = true/false
\newif\ifsetBiBLaTeX\setBiBLaTeXfalse         % BiBLaTeX = True / False

\newif\ifPHD@biblatex\PHD@biblatexfalse       % BiBLaTeX
\DeclareOption{biblatex}{
\ifsetBib
\ClassWarning{PhDThesisPSnPDF}{Bibliography selection conflict: A
bibliography style aleady specified. Please check the document class
options in case you have defined two bibliography styles.}
\else
\PHD@biblatextrue
\fi
}

\newif\ifPHD@authoryear\PHD@authoryearfalse   % Author-Year citation
\DeclareOption{authoryear}{
\ifsetBib
\ClassWarning{PhDThesisPSnPDF}{Bibliography selection conflict: A
bibliography style aleady specified. Please check the document class
options in case you have defined two bibliography styles.}
\else
\PHD@authoryeartrue
\setBibtrue
\fi
}

\newif\ifPHD@numbered\PHD@numberedfalse       % Numbered citiation
\DeclareOption{numbered}{
\ifsetBib
\ClassWarning{PhDThesisPSnPDF}{Bibliography selection conflict: A
bibliography style aleady specified. Please check the document class
options in case you have defined two bibliography styles.}
\else
\PHD@numberedtrue
\setBibtrue
\fi
}

\newif\ifuseCustomBib\useCustomBibfalse     % Custom Bibliography
\DeclareOption{custombib}{
\ifsetBib
\ClassWarning{PhDThesisPSnPDF}{Bibliography selection conflict: A
bibliography style aleady specified. Please check the document class
options in case you have defined two bibliography styles.}
\else
\ifPHD@biblatex
\ClassWarning{PhDThesisPSnPDF}{Bibliography selection conflict: A
bibliography style aleady specified. Please check the document class
options in case you have defined two bibliography styles.}
\else
\useCustomBibtrue
\setBibtrue
\fi
\fi
}

% ************************* Header / Footer Styling ****************************
\newif\ifPHD@textJustify\PHD@textJustifytrue % Set Justification true
\DeclareOption{flushleft}{\PHD@textJustifyfalse}


% ************************* Header / Footer Styling ****************************
\newif\ifPHD@pageStyleI\PHD@pageStyleIfalse % Set Page StyleI
\DeclareOption{PageStyleI}{\PHD@pageStyleItrue}

\newif\ifPHD@pageStyleII\PHD@pageStyleIIfalse % Set Page StyleII
\DeclareOption{PageStyleII}{\PHD@pageStyleIItrue}

% ***************************** Custom Margins  ********************************
\newif\ifsetCustomMargin\setCustomMarginfalse % Set Custom Margin
\newif\ifsetMargin\setMarginfalse % Set Custom Margin
\DeclareOption{custommargin}{\setCustomMargintrue}

% *************************** Pre-defined Options ******************************

% Font Size
\newcommand\PHD@ptsize{12pt} %Set Default Size as 12

\DeclareOption{10pt}{
\ClassWarning{PhDThesisPSnPDF}{The Cambridge University PhD thesis guidelines
recommend using a minimum font size of 11pt (12pt is preferred) and 10pt for
footnotes.}
\renewcommand\PHD@ptsize{10pt}
}
\DeclareOption{11pt}{\renewcommand\PHD@ptsize{11pt}}%
\DeclareOption{12pt}{\renewcommand\PHD@ptsize{12pt}}%
\PassOptionsToClass{\PHD@ptsize}{book}%
\message{PhDThesisPSnPDF: Font size is set as \PHD@ptsize}

% Page Size
\newcommand\PHD@papersize{a4paper} % Set Default as a4paper

\DeclareOption{a4paper}{\renewcommand\PHD@papersize{a4paper}}
\DeclareOption{a5paper}{\renewcommand\PHD@papersize{a5paper}}
\DeclareOption{letterpaper}{
\ClassWarning{PhDThesisPSnPDF}{The Cambridge University Engineering Deparment
PhD thesis guidelines recommend using A4 or A5paper}
\renewcommand\PHD@papersize{letterpaper}
}

\PassOptionsToClass{\PHD@papersize}{book}%

% Column layout
\DeclareOption{oneside}{\PassOptionsToClass{\CurrentOption}{book}}%
\DeclareOption{twoside}{\PassOptionsToClass{\CurrentOption}{book}}%

% Generates Warning for unknown options
\DeclareOption*{
\ClassWarning{PhDThesisPSnPDF}{Unknown or non-standard option
'\CurrentOption'. I'll see if I can load it from the book class. If you get a
warning unused global option(s): `\CurrentOption` then the option is not
supported!}
\PassOptionsToClass{\CurrentOption}{book}
}

% Determine whether to run pdftex or dvips
\ProcessOptions\relax%
\newif\ifsetDVI\setDVIfalse
\ifx\pdfoutput\undefined
% we are not running PDFLaTeX
\setDVItrue
\LoadClass[dvips,fleqn,openright]{book}%
\else % we are running PDFLaTeX
\ifnum \pdfoutput>0
%PDF-Output
\setDVIfalse
\LoadClass[pdftex,fleqn,openright]{book}%
\else
%DVI-output
\setDVItrue
\LoadClass[fleqn,openright]{book}%
\fi
\fi



% ******************************************************************************
% ******************************** Packages ************************************
% ******************************************************************************
% ************************** Layout and Formatting *****************************
\renewcommand\pdfshellescape{1}
\RequirePackage{lscape}   % Supports Landscape Layout
\RequirePackage{setspace} % Define line spacing in paragraph
\RequirePackage{calc}     % To calculate vertical spacing

% ************************* Conditional Statements *****************************
\RequirePackage{ifthen}  % conditional statements
\RequirePackage{ifpdf}    % Check for pdfLaTeX


% *********************** Table of Contents & Appendices ***********************
% add Bibliography, List of figures and tables to contents
\RequirePackage{tocbibind}

\renewcommand{\contentsname}{Table of contents}
\renewcommand{\listfigurename}{List of figures}
\renewcommand{\listtablename}{List of tables}


% *************************** Graphics and Figures *****************************
\RequirePackage[usenames, dvipsnames]{color}
\ifpdf
% Convert eps figures to pdf
\RequirePackage{epstopdf}
\RequirePackage[pdftex]{graphicx}
\DeclareGraphicsExtensions{.png, .jpg, .pdf}
\pdfcompresslevel=9
\graphicspath{{Figs/Raster/}{Figs/}}
\else
\RequirePackage{graphicx}
\DeclareGraphicsExtensions{.eps, .ps}
\graphicspath{{Figs/Vector/}{Figs/}}
\fi
\RequirePackage[multidot]{grffile}



% ******************************* Time Stamp ***********************************
% Compute the timestamp based on an idea of
% Tim Piessens \texttt{<Tim.Piessens@esat.kuleuven.ac.be>}.

\RequirePackage{datetime}

\newcount\PHD@hour \newcount\PHD@minute
\PHD@hour=\time
\divide \PHD@hour by 60
\PHD@minute=\time
\count@=\PHD@hour
\multiply \count@ by -60
\advance \PHD@minute by \count@
\newcommand{\PHD@daytime}{%
\today\space--\space%
\ifnum\PHD@hour=0 00\else\ifnum\PHD@hour<10 0\fi%
\number\PHD@hour\fi:\ifnum\PHD@minute<10 0\fi\number\PHD@minute
}

% ******************************* Draft Mode ***********************************
% Initializing Draft Text
\newcommand\SetDraftText[1]{}
% Initializing Draft Version
\newcommand\SetDraftVersion[1]{}
% Initializing Draft Content
\newcommand\SetDraftWMPosition[1]{}
% Initializing Draft Gray Scale
\newcommand\SetDraftGrayScale[1]{}

% ******************************* Bibliography *********************************
\ifPHD@authoryear
\ifPHD@biblatex
\RequirePackage[backend=biber, style=authoryear, citestyle=alphabetic,
sorting=nty, natbib=true]{biblatex}
\setBiBLaTeXtrue
\else
\RequirePackage[round, sort, numbers, authoryear]{natbib} %author year
\fi
\else
\ifPHD@numbered
\ifPHD@biblatex
\RequirePackage[backend=biber, style=numeric-comp,
citestyle=numeric, sorting=none, natbib=true]{biblatex}
\setBiBLaTeXtrue
\else
\RequirePackage[numbers,sort&compress]{natbib} % numbered citation
\fi
\else
\ifuseCustomBib
\AtBeginDocument{
\@ifpackageloaded{natbib}{}{
\@ifpackageloaded{biblatex}{}{
\ClassWarning{PhDThesisPSnPDF}{%
Custom bibliography is chosen, but no corresponding package
(biblatex/natbib) has been loaded. Please load the
appropriate bibliography package in the preamble.}
}
}
}
\else                                            % set default to numbered
\ifPHD@biblatex
\RequirePackage[backend=biber, style=numeric-comp,
citestyle=numeric, sorting=none, natbib=true]{biblatex}
\setBiBLaTeXfalse
\else
\RequirePackage[numbers,sort&compress]{natbib}
\fi % default
\setBibfalse
\fi % custombib
\fi % numbered
\fi % author year

\ifsetBib
\else
\ClassWarning{PhDThesisPSnPDF}{No bibliography style was specified.
Default numbered style is used. If you would like to use a
different style, use `authoryear' or `numbered' in the options in
documentclass or use `custombib` and define the natbib package or
biblatex package with required style in the Preamble.tex file}
\fi

% *********************** To copy ligatures and Fonts **************************
\RequirePackage{textcomp}
% Font Selection
\ifPHD@times
\RequirePackage{mathptmx}  % times roman, including math (where possible)
\setFonttrue
\message{PhDThesisPSnPDF: Using Times Roman font}
\else
\ifPHD@fourier
\RequirePackage{fourier} % Fourier
\setFonttrue
\message{PhDThesisPSnPDF: Using Fourier font}
\else
\ifsetCustomFont
\setFonttrue
\message{PhDThesisPSnPDF: Using custom font}
\else
\setFontfalse
\message{PhDThesisPSnPDF: No font is set}
\fi % custom font
\fi % Fourier font
\fi % Times font

% If Font is not set throw a warning.
\ifsetFont
\else
\ClassWarning{PhDThesisPSnPDF}{Using default font Latin Modern. If you
would like to use other pre-defined fonts use `times' (The Cambridge
University PhD thesis guidelines recommend using Times font)  or `fourier'
or load a custom font in the preamble.tex file by specifying `customfont'
in the class options}
\RequirePackage{lmodern}
\fi

\RequirePackage[utf8]{inputenc}
\RequirePackage[T1]{fontenc}

\input{glyphtounicode}
\pdfglyphtounicode{f_f}{FB00}
\pdfglyphtounicode{f_i}{FB01}
\pdfglyphtounicode{f_l}{FB02}
\pdfglyphtounicode{f_f_i}{FB03}
\pdfglyphtounicode{f_f_l}{FB04}
\pdfgentounicode=1


%******************************* Print / Online ********************************
% Defines a print / online version to define page-layout and hyperrefering

% Moved below other usepackage definitions to fix PDFLaTeX footnote warning
% Based on the suggestion by John Plaice
\ifsetDVI
\special{papersize=\the\paperwidth,\the\paperheight}
\RequirePackage[dvips,unicode=true]{hyperref}
\else
\RequirePackage[unicode=true]{hyperref}
\pdfpagewidth=\the\paperwidth
\pdfpageheight=\the\paperheight
\fi

\if@print
% For Print version
\hypersetup{
final=true,
plainpages=false,
pdfstartview=FitV,
pdftoolbar=true,
pdfmenubar=true,
bookmarksopen=true,
bookmarksnumbered=true,
breaklinks=true,
linktocpage,
colorlinks=true,
linkcolor=black,
urlcolor=black,
citecolor=black,
anchorcolor=black
}
\ifsetCustomMargin
% Margin to be define in preamble using geometry package
\else
\ifsetDVI
% Odd and Even side Margin for binding and set viewmode for PDF
\RequirePackage[dvips,paper=\PHD@papersize,hmarginratio=1:1,
vmarginratio=1:1,scale=0.75,bindingoffset=5mm]{geometry}
\else
\RequirePackage[pdftex,paper=\PHD@papersize,hmarginratio=1:1,
vmarginratio=1:1,scale=0.75,bindingoffset=5mm]{geometry}
\fi
\fi

\if@twoside
\hypersetup{pdfpagelayout=TwoPageRight}
\else
\hypersetup{pdfpagelayout=OneColumn}
\fi

\else
% For PDF Online version
\hypersetup{
final=true,
plainpages=false,
pdfstartview=FitV,
pdftoolbar=true,
pdfmenubar=true,
bookmarksopen=true,
bookmarksnumbered=true,
breaklinks=true,
linktocpage,
colorlinks=true,
linkcolor=blue,
urlcolor=blue,
citecolor=blue,
anchorcolor=green
}

\ifsetCustomMargin
% Margin to be define in preamble using geometry package
\else
% No Margin staggering on Odd and Even side
\ifsetDVI
\RequirePackage[dvips,paper=\PHD@papersize,hmarginratio=1:1,
vmarginratio=1:1,scale=0.75]{geometry}
\else
\RequirePackage[pdftex,paper=\PHD@papersize,hmarginratio=1:1,
vmarginratio=1:1,scale=0.75]{geometry}
\fi
\fi

\hypersetup{pdfpagelayout=OneColumn}
\fi

% Backward compatibility - setMargin is now replaced with customMargin
\ifsetCustomMargin
\setMarginfalse
\else
\setMargintrue
\fi

% ************************ URL Package and Definition **************************
\RequirePackage{url}
% Redefining urlstyle to use smaller fontsize in References with URLs
\newcommand{\url@leostyle}{%
\@ifundefined{selectfont}{\renewcommand{\UrlFont}{\sffamily}}
{\renewcommand{\UrlFont}{\normalsize}}}
\urlstyle{leo}

% option to split urls over multiple lines for latex >> DVIPS >> PDF option
% PDFLaTeX does it automatically.

\ifsetDVI
\RequirePackage{breakurl} % to split the url over multiple lines
\fi


% ******************************************************************************
% **************************** Pre-defined Settings ****************************
% ******************************************************************************

% *************************** Setting PDF Meta-Data ****************************
\ifpdf
\AtBeginDocument{
\hypersetup{
pdftitle = {\@title},
pdfauthor = {\@author}
}
}
\fi

% ******************************** Line Spacing ********************************
% Set spacing as 1.5 line spacing for the PhD Thesis
% In practice, fortunately, nobody knows really what “one-and-a-half spaced
% type” means exactly (in terms of millimetres baseline distance). The following
% LaTeX setting has routinely been considered perfectly acceptable:

\renewcommand\baselinestretch{1.5}

% ************************** TOC and Hide Sections *****************************
\newcommand{\nocontentsline}[3]{}
\newcommand{\tochide}[2]{
\bgroup\let
\addcontentsline=\nocontentsline#1{#2}
\egroup}
% Removes pagenumber appearing from TOC
\addtocontents{toc}{\protect\thispagestyle{empty}}


% ***************************** Header Formatting ******************************
% Custom Header with Chapter Number, Page Number and Section Numbering

\RequirePackage{fancyhdr} % Define custom header

% Set Fancy Header Command is defined to Load FancyHdr after Geometry is defined
\newcommand{\setFancyHdr}{

\pagestyle{fancy}
\ifPHD@pageStyleI
% Style 1: Sets Page Number at the Top and Chapter/Section Name on LE/RO
\renewcommand{\chaptermark}[1]{\markboth{##1}{}}
\renewcommand{\sectionmark}[1]{\markright{\thesection\ ##1\ }}
\fancyhf{}
\fancyhead[RO]{\nouppercase \rightmark\hspace{0.25em} |
\hspace{0.25em} \bfseries{\thepage}}
\fancyhead[LE]{ {\bfseries\thepage} \hspace{0.25em} |
\hspace{0.25em} \nouppercase \leftmark}


\else
\ifPHD@pageStyleII
% Style 2: Sets Page Number at the Bottom with Chapter/Section Name on LO/RE
\renewcommand{\chaptermark}[1]{\markboth{##1}{}}
\renewcommand{\sectionmark}[1]{\markright{\thesection\ ##1}}
\fancyhf{}
\fancyhead[RO]{\bfseries\nouppercase \rightmark}
\fancyhead[LE]{\bfseries \nouppercase \leftmark}
\fancyfoot[C]{\thepage}


\else
% Default Style: Sets Page Number at the Top (LE/RO) with Chapter/Section Name
% on LO/RE and an empty footer
\renewcommand{\chaptermark}[1]{\markboth {##1}{}}
\renewcommand{\sectionmark}[1]{\markright{\thesection\ ##1}}
\fancyhf{}
\fancyhead[LO]{\nouppercase \rightmark}
\fancyhead[LE,RO]{\bfseries\thepage}
\fancyhead[RE]{\nouppercase \leftmark}
\fi

\fi
}

\setlength{\headheight}{14.5pt}
%\renewcommand{\headrulewidth}{0.5pt}
%\renewcommand{\footrulewidth}{0pt}
\fancypagestyle{plain}{
\fancyhead{}
\renewcommand{\headrulewidth}{0pt}
}

% If Margin has been set (default margin print/online version)
\ifsetCustomMargin
\AtBeginDocument{
\@ifpackageloaded{geometry}{}{\ClassWarning{PhDThesisPSnPDF}{%
Custom margin is chosen, but geometry package is not loaded. Please load the
`geometry' package in the preamble.}}}
\else
\setFancyHdr % Apply fancy header settings otherwise apply it in preamble
\fi

% **************** Clear Header Style on the Last Empty Odd pages **************
\renewcommand{\cleardoublepage}{\clearpage\if@twoside \ifodd\c@page\else%
\hbox{}%
\thispagestyle{empty}  % Empty header styles
\newpage%
\if@twocolumn\hbox{}\newpage\fi\fi\fi}

% These macros define an environment for front matter that is always
% single column even in a double-column document.
\newenvironment{alwayssingle}{%
\@restonecolfalse\if@twocolumn\@restonecoltrue\onecolumn
\else\newpage\fi}
{\if@restonecol\twocolumn\else\newpage\fi}

% Set single column even under two column layout
\newcommand{\setsinglecolumn}{
\if@twocolumn
\onecolumn
\else
\fi
}

% ******************************* Nomenclature *********************************
\RequirePackage{nomencl}
\makenomenclature
\renewcommand{\nomgroup}[1]{%
\ifthenelse{\equal{#1}{A}}{\item[\textbf{Roman Symbols}]}{%
\ifthenelse{\equal{#1}{G}}{\item[\textbf{Greek Symbols}]}{%
\ifthenelse{\equal{#1}{Z}}{\item[\textbf{Acronyms / Abbreviations}]}{%
\ifthenelse{\equal{#1}{R}}{\item[\textbf{Superscripts}]}{%
\ifthenelse{\equal{#1}{S}}{\item[\textbf{Subscripts}]}{%
\ifthenelse{\equal{#1}{X}}{\item[\textbf{Other Symbols}]}
{}
}% matches mathematical symbols > X
}% matches Subscripts           > S
}% matches Superscripts         > R
}% matches Abbreviations        > Z
}% matches Greek Symbols        > G
}% matches Roman Symbols        > A

% To add nomenclature in the header
\renewcommand{\nompreamble}{\markboth{\nomname}{\nomname}}

% Add nomenclature to contents and print out nomenclature
\newcommand{\printnomencl}[1][]{
\ifthenelse{\equal {#1}{}}
{\printnomenclature}
{\printnomenclature[#1]}
\addcontentsline{toc}{chapter}{\nomname}
}

\renewcommand\backmatter{\appendix
\def\chaptermark##1{\markboth{%
\ifnum  \c@secnumdepth > \m@ne  \@chapapp\ \thechapter:  \fi  ##1}{%
\ifnum  \c@secnumdepth > \m@ne  \@chapapp\ \thechapter:  \fi  ##1}}%
\def\sectionmark##1{\relax}}

% ***************************** Create the index *******************************
\ifPHD@index
\RequirePackage{makeidx}
\makeindex
\newcommand{\printthesisindex}{
\cleardoublepage
\phantomsection
\printindex}
\else
\newcommand{\printthesisindex}{}
\fi
