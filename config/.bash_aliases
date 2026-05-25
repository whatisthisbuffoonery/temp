alias C='clang -Wall -Wextra -Werror -g'
alias V='valgrind --track-origins=yes --leak-check=full --track-fds=yes --trace-children=yes -s'
alias vimbash='vim ~/.bash_aliases'
alias Sbash='source ~/.bash_aliases'
alias P='python3'
alias CX='chmod +x'
alias ls='la'
alias mv='mv -i'
alias cp='cp -i'

ff() {
	local pattern="$1"
	shift #removes $1 search pattern from list of files

	local files
	local tgt
	if [ $# -gt 0 ]; then
		files=("${@}")
		tgt="${files[0]}"
	else
		files=( ./* )
		tgt="./*"
	fi
	if [ ${#files[@]} -eq 0 ] || [ ! -e "${files[0]}" ]; then
		echo "no files exist: ${files[0]:-"./*"}"
		return 1
	fi

	local banana=$(grep -ln --exclude="*.o" --exclude="*.git" --exclude="*.out" "$pattern" "${files[@]}" 2>/dev/null)
	if [ ${#banana[@]} -eq 0 ] || [ ! -e "${banana[0]}" ]; then
		echo "no matches found: ${pattern} in ${tgt}"
		return 1
	fi
	local output=$(echo "$banana" | fzf)
	if [[ -n "$output" ]]; then
		echo "$output"
		vim "$output"
	fi
}
