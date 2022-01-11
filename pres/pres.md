Using C in R
========================================================
author: Hugh
date:
autosize: true

Motivation
========================================================
incremental: true

Why use C?

1. Performance


Motivation
========================================================
incremental: true

**When** to use C?

1. 'Performance'
2. When it's the right tool for the job


Motivation (concretely)
========================================================

When to use C?

* If you have to ask "how do I do this in `dplyr`?"
* If you're allocating largeish vectors only to make the next step in the calculation easier/possible
* You're essentially only handling atomic, numeric vectors
* You want to paralellize a simple operation

When not to use C?

* If you're not willing to be careful about memory leaks
* You're not writing a package
* You can't count (accurately)

Crash course in C
========================================================

* "compiled" language.
* Not like R
* Not like C either?


C is not R
========================================================
incremental: true

In R, you'd write:


```r
x <- c(1, 5, 3)
y <- 3
```

In C,


```c
double x[3] = {1, 5, 3};
double y = 3;
```

i.e. you need to be explicit about what you're creating, and you need to put semicolons
at the end of expressions

C is not R
========================================================


```r
has4 <- function(x) {
  n <- length(x)
  for (i in 1:n) {
    if (x[i] == 4) {
      return(TRUE)
    }
  }
  return(FALSE)
}
```


```c
bool has4(SEXP x) {
  R_xlen_t n = xlength(x);
  for (R_xlen_t i = 0; i < N; ++i) {
    if (REAL(x)[i] == 4) {
      return true;
    }
  }
  return false;
}
```

C is not R
========================================================
incremental: true
With functions, you have to declare what the function returns, and the
type of each input. (`bool` and `SEXP`)

Wait, what is `SEXP` and what is `REAL()`? They're not standard C.

(Answer: this is R's interface to C.)


Using C in a package
========================================================

* Write C code in `.c` files and put them in `./src/`
* In your R folder, use `.Call` inside an R function
* Compile your package
* Call your R function

Using C in a package
========================================================

* **Lots of boilerplate**
* Write C code in `.c` files and put them in `./src/`
* In your R folder, use `.Call` inside an R function
* Compile your package
* Call your R function


Using C in a package
========================================================




