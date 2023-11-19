# yt-ttml2txt

> Note to Github users : development is happening on [Gitlab](https://gitlab.com/oelmekki/yt-ttml2txt),
> please go there if you want to open issues or submit merge request.

Converts a Youtube TTML subtitle file to a text file.

## Install

```
make                                 # build with gcc
sudo make install                    # install in /usr/local/bin/

# Alternatives
make CC=clang                        # build with an other compiler, here clang
sudo make install PREFIX=/usr/bin/   # install in an other place, here /usr/bin/
```

## Usage

```
yt-ttml2txt [-1] <file>

Converts a TTML subtitle file to a text file, written on STDOUT.

Options:

`-1`: print all in one line (eg to facilitate grepping).
```

Note that this is very simple parsing tested only against Youtube's TTML
files and probably only working with them.

My goal is not to fully support any valid TTML file, just what Youtube
produces. If this simple parsing turns out to be unstable, I'll rewrite it
into a full blown AST parser.

## Why?

I wrote this to be able to dump text content for youtube videos and then
grep then, providing local full text search for youtube videos I care
about. Here is how I do it (you need [yt-dlp](https://github.com/yt-dlp/yt-dlp) for that):

```
yt-dlp --skip-download --write-auto-sub --sub-format ttml <youtube-video-url>
yt-ttml2txt -1 <ttml-file> > <cache_dir>/<ttml-file.txt>
grep -r "<your query>" <cache_dir>/
```

You now can grep your favorite videos content locally for the low price of
a few text files in storage.

## Credits

This idea came after reading Jeff Atwood mentions
[his use of Youtube subtitles to access content](https://infosec.exchange/@codinghorror/111433268487559172).
