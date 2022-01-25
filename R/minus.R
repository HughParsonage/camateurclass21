
minus <- function(x, y) {
  stopifnot(is.numeric(x))
  ans <- .Call("C_minus", x, y, PACKAGE = utils::packageName())
  if (is.null(ans)) {
    warning("Cheating!")
    return(x - y)
  }
  ans
}

