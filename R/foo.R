#'
#' @export

do_foo <- function() {
  .Call("print_foo", NULL, PACKAGE = utils::packageName())
}

do_good_add <- function(x, y) {
  .Call("Add2", x, y, PACKAGE = utils::packageName())
}

add3 <- function(x, y) {
  .Call("Add3", x, y, PACKAGE = utils::packageName())
}

Any_more_than_2 <- function(x, y) {
  .Call("any_more_than_2", x, y, PACKAGE = utils::packageName())
}

Rany_more_than_2 <- function(x, y) {
  z <- x - y
  w <- z > 2
  which.max(w)
}
