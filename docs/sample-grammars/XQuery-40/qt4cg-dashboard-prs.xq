(:~
 : Fetch the QT4 CG dashboard and return the open PR path segments.
 :)

(:~ The QT4 CG dashboard URL. :)
declare variable $dashboard-url external := 'https://qt4cg.org/dashboard/';

(:~
 : Keep the first occurrence of each value, preserving dashboard order.
 :
 : @param $values the values to filter
 : @return the distinct values in first-seen order
 :)
declare function local:distinct-in-order($values as xs:string*) as xs:string*
{
  for $value at $pos in $values
  where empty(index-of(subsequence($values, 1, $pos - 1), $value))
  return $value
};

(:~
 : Extract PR numbers from a text fragment.
 :
 : @param $text the source text
 : @param $pattern a regular expression that captures the PR number in group 1
 : @return the captured PR numbers
 :)
declare function local:prs($text as xs:string, $pattern as xs:string) as xs:string*
{
  analyze-string($text, $pattern)
  /*:match
  ! replace(., $pattern, '$1')
};

let $dashboard := unparsed-text($dashboard-url)
let $after-open-prs := substring-after($dashboard, 'Open PRs:')
let $open-prs :=
  if (contains($after-open-prs, 'Pull requests in descending order')) then
    substring-before($after-open-prs, 'Pull requests in descending order')
  else
    $after-open-prs
let $open-numbers := local:distinct-in-order(local:prs($open-prs, '#([0-9]+)'))
let $numbers :=
  if (exists($open-numbers)) then
    $open-numbers
  else
    local:distinct-in-order(local:prs($dashboard, 'PR\s+#([0-9]+)'))
return
  string-join($numbers ! ('pr/' || .), '&#xA;')
