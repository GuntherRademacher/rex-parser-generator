let $grd := unparsed-text('unacceptable-keywords.txt') => tokenize('[ &#xA;&#xD;]+')
let $jwl := unparsed-text('jwl-unacceptable-keywords.txt') => tokenize('[ &#xA;&#xD;]+')
let $mhk := unparsed-text('mhk-unacceptable-keywords.txt') => tokenize('[ &#xA;&#xD;]+')
return $mhk[not(. = $jwl)]