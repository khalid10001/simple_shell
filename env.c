#include "shell.h"

/**
 * setEnvVariable - Set or modify an environment variable.
 * @variable: Name of the environment variable.
 * @value: Value to set for the environment variable.
 * @env: Array of environment variables.
 * Return: 0 on success, -1 on failure.
 */
int setEnvVariable(char *variable, char *value, char **env)
{
    int index = 0;
    char *newEnvVar = NULL;

    /* Loop through the environment variables to find the specified variable */
    while (env[index])
    {
        /* Check if the variable exists in the environment */
        if (compareStringsN(env[index], variable, getStringLength(variable)) == 0)
        {
            /* Update the value of the existing variable */
            newEnvVar = malloc(sizeof(char) * (getStringLength(variable) + getStringLength(value) + 2));
            if (!newEnvVar)
                return (-1);
            copyString(newEnvVar, variable);
            concatenateStrings(newEnvVar, "=");
            concatenateStrings(newEnvVar, value);
            /* Replace the existing environment variable with the updated one */
            free(env[index]);
            env[index] = newEnvVar;

            return (0);
        }
        index++;
    }
    /* If the variable doesn't exist, create a new one */
    newEnvVar = malloc(sizeof(char) * (getStringLength(variable) + getStringLength(value) + 2));
    if (!newEnvVar)
        return (-1);
    copyString(newEnvVar, variable);
    concatenateStrings(newEnvVar, "=");
    concatenateStrings(newEnvVar, value);
    /* Add the new environment variable to the array */
    env[index] = newEnvVar;
    env[index + 1] = NULL;

    return (0);
}

/**
 * unsetEnvVariable - Remove an environment variable.
 * @variable: Name of the environment variable to remove.
 * @env: Array of environment variables.
 * Return: 0 on success, -1 on failure.
 */
int unsetEnvVariable(char *variable, char **env)
{
    int index = 0, found = 0;

    /* Loop through the environment variables to find and remove the specified variable */
    while (env[index])
    {
        /* Check if the variable exists in the environment */
        if (compareStringsN(env[index], variable, getStringLength(variable)) == 0)
        {
            /* Free the memory allocated for the environment variable */
            free(env[index]);

            /* Move the remaining variables to fill the gap */
            while (env[index + 1])
            {
                env[index] = env[index + 1];
                index++;
            }

            /* Mark the end of the environment variables array */
            env[index] = NULL;

            found = 1;
            break;
        }
        index++;
    }

    if (found)
        return (0);
    else
        return (-1);
}
