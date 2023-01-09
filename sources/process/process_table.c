/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 20:05:53 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/09 16:39:06 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
  Initialise process list - DONE
  functions that inits || appends
  function that deletes node from any position
  dont wait on the child process if does not contain &
  if & sign is present. Fetch the process ID of child process

  jobs:
  if pid still processing then it is running.
  if pid is complete, then display done -> delete node

  man 2 pause() -> pauses a signal
  man 2 kill() -> to check if process is still running
  
*/