#include "shell.h"

int setEnvVariable(char *variable, char *value, char **env)
{
    int index = 0;
    char *newEnvVar = NULL;
    char **newEnv;
    int i;

    while (env[index])
    {
        if (compareStringsN(env[index], variable, getStringLength(variable)) == 0)
        {
            free(env[index]);
            newEnvVar = malloc(sizeof(char) * (getStringLength(variable) + getStringLength(value) + 2));
            if (!newEnvVar)
                return (-1);

            copyString(newEnvVar, variable);
            concatenateStrings(newEnvVar, "=");
            concatenateStrings(newEnvVar, value);

            env[index] = newEnvVar;

            return (0);
        }
        index++;
    }

    newEnvVar = malloc(sizeof(char) * (getStringLength(variable) + getStringLength(value) + 2));
    if (!newEnvVar)
        return (-1);

    copyString(newEnvVar, variable);
    concatenateStrings(newEnvVar, "=");
    concatenateStrings(newEnvVar, value);

    
    newEnv = malloc(sizeof(char *) * (index + 2));
    if (!newEnv)
    {
        free(newEnvVar);
        return (-1);
    }


    for (i = 0; i < index; i++)
        newEnv[i] = env[i];

    newEnv[index] = newEnvVar;
    newEnv[index + 1] = NULL;

    
    free(env);

    
    env = newEnv;

    return (0);
}

int unsetEnvVariable(char *variable, char **env)
{
    int index = 0, found = 0;

    while (env[index])
    {
        if (compareStringsN(env[index], variable, getStringLength(variable)) == 0)
        {
            free(env[index]); 

            while (env[index + 1])
            {
                env[index] = env[index + 1];
                index++;
            }

            
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

