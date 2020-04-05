_coldecplot() {
	# Declare local variables and use long option splitting
	local cur prev words cword split
	_init_completion -s || return

	# Don't continue completion after one of these options are given
	case $prev in
		--help|-!(-*)[h])
			return
			;;
	esac

	# Don't continue if the current long option was not split
    $split && return

	# Perform option completion
    if [[ $cur == -* ]]; then
		#  Only use the long options shown when using --help
        COMPREPLY=( $(compgen -W '$(_parse_help "$1")' -- "$cur") )

		#  Options followed by an equals sign are not appended with a space
        [[ $COMPREPLY == *= ]] && compopt -o nospace
    fi

	# Perform file and directory completion
	_filedir
}

complete -F _coldecplot coldecplot